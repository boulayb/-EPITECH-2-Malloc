/*
** free.c for malloc in /home/danilo_d/Epitech-Projects/Semestre4/Malloc-working
**
** Made by Danilov DImitri
** Login   <danilo_d@epitech.net>
**
** Started on Thu Feb 11 09:50:51 2016 Danilov DImitri
** Last update Sun Feb 14 20:10:34 2016 Arnaud Boulay
*/

#include <pthread.h>
#include <unistd.h>
#include "malloc.h"

t_block			*check_merge_top(t_block *current_block)
{
  t_block		*previous_block;
  int			previous_block_size;

  if ((void *)current_block > g_first_address + sizeof(t_block))
    {
      previous_block_size = *(int *)((void *)(current_block)
				     - (int)sizeof(int));
      if (previous_block_size <= 0)
	return (NULL);
      previous_block = (void *)(current_block) - previous_block_size;
      previous_block->size += current_block->size;
      previous_block->footer_size = current_block->footer_size;
      *previous_block->footer_size = previous_block->size;
      current_block->magic_number = 0;
      return (previous_block);
    }
  return (NULL);
}

t_block			*check_merge_bot(t_block *current_block)
{
  t_block		*next_block;

  if ((void *)current_block + current_block->size < sbrk(0))
    {
      next_block = (void *)current_block + current_block->size;
      if (next_block->magic_number == ALLOCATED_MAGIC_NUMBER
	  && *next_block->footer_size <= 0)
	return (NULL);
      if ((void *)next_block->next < g_first_address ||
	  next_block->next == NULL)
	return (NULL);
      current_block->size += next_block->size;
      next_block->magic_number = 0;
      next_block->back->next = next_block->next;
      next_block->next->back = next_block->back;
      return (next_block);
    }
  return (NULL);
}

int			handle_errors_free(void *ptr, t_block *free_block)
{
  if (ptr == NULL || (free_block->magic_number != FREE_MAGIC_NUMBER &&
		      free_block->magic_number != ALLOCATED_MAGIC_NUMBER) ||
      ptr <= g_first_address || ptr >= sbrk(0))
    {
      pthread_mutex_unlock(&g_lock);
      return (0);
    }
  if (free_block->magic_number == FREE_MAGIC_NUMBER)
    {
      write(2, "double free\n", 13);
      pthread_mutex_unlock(&g_lock);
      return (0);
    }
  return (1);
}

void			merge_previous_block(t_block *previous_block)
{
  t_block		*next_block;

  if ((next_block = check_merge_bot(previous_block)) != NULL)
    {
      previous_block->footer_size = (void *)next_block->footer_size;
      *previous_block->footer_size = previous_block->size;
    }
  if (previous_block->size > (unsigned int)getpagesize()
      && (void *)previous_block + previous_block->size == sbrk(0))
    {
      previous_block->back->next = previous_block->next;
      previous_block->next->back = previous_block->back;
      previous_block->back = NULL;
      previous_block->next = NULL;
      sbrk((int)previous_block->size * -1);
    }
}

void			free(void *ptr)
{
  t_block		*free_block;
  t_block		*previous_block;
  int			hashed_size;

  pthread_mutex_lock(&g_lock);
  free_block = ptr - sizeof(t_block);
  if (handle_errors_free(ptr, free_block) == 0)
    return ;
  previous_block = check_merge_top(free_block);
  if (previous_block != NULL)
    merge_previous_block(previous_block);
  else
    {
      check_merge_bot(free_block);
      hashed_size = hash_size_list(free_block->size);
      if (hashed_size < 0)
	hashed_size = 0;
      if (free_block->size > (unsigned int)getpagesize() &&
	  (void *)free_block + free_block->size == sbrk(0))
	sbrk((int)free_block->size * -1);
      else
	add_to_free_list(free_block, hashed_size);
    }
  pthread_mutex_unlock(&g_lock);
}
