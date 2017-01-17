/*
** hash.c for malloc in /home/danilo_d/Epitech-Projects/Semestre4/Malloc-working
**
** Made by Danilov DImitri
** Login   <danilo_d@epitech.net>
**
** Started on Thu Feb 11 09:50:15 2016 Danilov DImitri
** Last update Sun Feb 14 19:48:12 2016 Arnaud Boulay
*/

#include <unistd.h>
#include "malloc.h"

static size_t	intervals[] = {0, 40, 80, 160, 260, 520, 1040, 2040,
			       4080, 8160, 20000, 50000, 100000, 500000};

int		hash_size_list(size_t size)
{
  int		i;

  i = 0;
  while (i < NUMBER_INTERVALS - 1)
    {
      if (intervals[i] >= size)
	return (i);
      i++;
    }
  return (NUMBER_INTERVALS - 1);
}

t_block		*find_free_space_list(t_block *root, size_t size)
{
  t_block	*tmp;
  t_block	*closest;
  size_t	closest_size;

  tmp = root->next;
  closest = NULL;
  closest_size = 0;
  if (tmp != root && tmp->size >= size)
    {
      closest = tmp;
      closest_size = tmp->size;
    }
  tmp = tmp->next;
  if (tmp != root)
    {
      if (tmp->size < closest_size && tmp->size >= size)
	closest = tmp;
    }
  return closest;
}

t_block		*find_free_space_table(size_t size)
{
  int		hashed_size;
  t_block	*block;
  t_block	*ret;

  hashed_size = hash_size_list(size);
  block = g_free_table->table[hashed_size];
  while ((ret = find_free_space_list(block, size)) == NULL)
    {
      if (hashed_size == NUMBER_INTERVALS - 1)
	return (NULL);
      else
	hashed_size += 1;
      block = g_free_table->table[hashed_size];
    }
  return (ret);
}

void		change_table(t_block *block)
{
  int		hashed_size;

  hashed_size = hash_size_list(block->size);
  block->back->next = block->next;
  block->next->back = block->back;
  add_to_free_list(block, hashed_size);
}
