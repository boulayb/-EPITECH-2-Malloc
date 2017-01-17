/*
** new_malloc.c for malloc in /home/danilo_d/Epitech-Projects/Semestre4/Malloc-working
**
** Made by Danilov DImitri
** Login   <danilo_d@epitech.net>
**
** Started on Thu Feb 11 09:50:33 2016 Danilov DImitri
** Last update Sun Feb 14 19:36:11 2016 Arnaud Boulay
*/

#include <unistd.h>
#include <pthread.h>
#include "malloc.h"

pthread_mutex_t		g_lock;
t_table			*g_free_table;

int			add_to_free_list(t_block *block, int hashed_size)
{
  t_block		*tmp;

  block->magic_number = FREE_MAGIC_NUMBER;
  tmp = g_free_table->table[hashed_size];
  block->back = tmp->back;
  block->next = tmp;
  block->footer_size = (void *)(block) + block->size - (int)sizeof(int);
  *block->footer_size = block->size;
  tmp->back->next = block;
  tmp->back = block;
  return (0);
}

t_block			*allocate_space(size_t size)
{
  t_block		*data;
  int			hashed_size;
  size_t		bytes;

  bytes = getpagesize();
  bytes = bytes * ((size / bytes) + 1);
  if (bytes == 0)
    return (NULL);
  data = sbrk(bytes);
  if (data == (void *)-1)
    return (NULL);
  data->size = bytes;
  hashed_size = hash_size_list(size);
  add_to_free_list(data, hashed_size);
  return (data);
}

t_block			*split_memory(t_block *block, size_t size)
{
  t_block		*new_block;

  if (block->size - size > sizeof(t_block))
    {
      new_block = (void *)block + size;
      new_block->size = block->size - size;
      new_block->next = block->next;
      new_block->back = block->back;
      change_table(new_block);
      block->size = size;
    }
  else
    {
      block->back->next = block->next;
      block->next->back = block->back;
    }
  block->next = NULL;
  block->back = NULL;
  block->magic_number = ALLOCATED_MAGIC_NUMBER;
  block->footer_size = (void *)block + block->size - (int)sizeof(int);
  *block->footer_size = (int)(block->size * -1);
  return (block);
}

void			*malloc(size_t size)
{
  t_block		*ret;

  pthread_mutex_lock(&g_lock);
  size += (int)sizeof(t_block) + sizeof(int);
  if (size % 8 != 0)
    size += (8 - (size % 8));
  if (g_free_table == NULL)
    if (create_free_table(size) == 1)
      {
	pthread_mutex_unlock(&g_lock);
	return (NULL);
      }
  if ((ret = find_free_space_table(size)) == NULL)
    {
      ret = allocate_space(size);
      if (ret == NULL)
	{
	  write(2, "sbrk failed\n", 13);
	  pthread_mutex_unlock(&g_lock);
	  return (NULL);
	}
    }
  ret = split_memory(ret, size);
  pthread_mutex_unlock(&g_lock);
  return ((void *)ret + sizeof(t_block));
}
