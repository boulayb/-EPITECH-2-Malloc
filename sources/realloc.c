/*
** realloc.c for malloc in /home/danilo_d/Epitech-Projects/Semestre4/Malloc-working
**
** Made by Danilov DImitri
** Login   <danilo_d@epitech.net>
**
** Started on Thu Feb 11 09:51:07 2016 Danilov DImitri
** Last update  Thu Feb 11 09:51:07 2016 Danilov DImitri
*/

#include <string.h>
#include "malloc.h"

void		*realloc(void *ptr, size_t size)
{
  void		*new_address;
  t_block	*block;
  size_t	previous_size;

  if (ptr == NULL)
    return (malloc(size));
  block = ptr - sizeof(t_block);
  if (block->magic_number != ALLOCATED_MAGIC_NUMBER
      && block->magic_number != FREE_MAGIC_NUMBER)
    return (malloc(size));
  new_address = malloc(size);
  previous_size = block->size - sizeof(t_block);
  if (previous_size < size)
    memcpy(new_address, ptr, previous_size);
  else
    memcpy(new_address, ptr, size);
  free(ptr);
  return (new_address);
}
