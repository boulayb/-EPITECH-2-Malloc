/*
** calloc.c for malloc in /home/danilo_d/Epitech-Projects/Semestre4/Malloc-working
**
** Made by Danilov DImitri
** Login   <danilo_d@epitech.net>
**
** Started on Thu Feb 11 09:51:20 2016 Danilov DImitri
** Last update Sun Feb 14 19:40:24 2016 Arnaud Boulay
*/

#include <stdlib.h>
#include <string.h>
#include "malloc.h"

void		*calloc(size_t nmemb, size_t size)
{
  void		*mem;
  size_t	total_size;

  if (nmemb == 0 || size == 0)
    return (NULL);
  total_size = nmemb * size;
  mem = malloc(total_size);
  if (mem == NULL)
    return (NULL);
  return (memset(mem, 0, total_size));
}
