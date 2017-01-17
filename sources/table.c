/*
** table.c for malloc in /home/danilo_d/Epitech-Projects/Semestre4/PSU_2015_malloc/sources
**
** Made by Danilov DImitri
** Login   <danilo_d@epitech.net>
**
** Started on Sat Feb 13 15:25:40 2016 Danilov DImitri
** Last update Sun Feb 14 19:50:33 2016 Arnaud Boulay
*/

#include <unistd.h>
#include "malloc.h"

void		*g_first_address;

void		*fill_table(void *address)
{
  int		i;

  i = 0;
  while (i < NUMBER_INTERVALS)
    {
      g_free_table->table[i] = address;
      g_free_table->table[i]->next = g_free_table->table[i];
      g_free_table->table[i]->back = g_free_table->table[i];
      i++;
      address += sizeof(t_block);
    }
  return (address);
}

int		init_memory_table(size_t size)
{
  size_t	bytes;

  bytes = getpagesize();
  bytes = bytes * ((size / bytes) + 1);
  return (bytes);
}

int		create_free_table(size_t size)
{
  void		*data;
  void		*address;
  t_block	*new_page;
  int		hashed_size;
  int		total_size;

  if ((total_size = init_memory_table((sizeof(t_table) +
				       ((sizeof(t_block) *
					 NUMBER_INTERVALS - 1)) + 1)
				      + size)) == 0)
    return (1);
  data = sbrk(total_size);
  if (data == (void *)-1)
    return (1);
  g_free_table = data;
  g_free_table->intervals = NUMBER_INTERVALS;
  address = data + sizeof(t_table);
  new_page = fill_table(address);
  g_first_address = new_page;
  new_page->size = total_size -
    (sizeof(t_table) + ((sizeof(t_block) * NUMBER_INTERVALS - 1)) + 1);
  hashed_size = hash_size_list(new_page->size);
  add_to_free_list(new_page, hashed_size);
  return (0);
}
