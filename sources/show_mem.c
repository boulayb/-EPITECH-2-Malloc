/*
** showMem.c for malloc in /home/boulay_b/Rendu/SE4/PSU/PSU_2015_malloc
**
** Made by Arnaud Boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Tue Feb  9 15:26:47 2016 Arnaud Boulay
** Last update Sun Feb 14 20:10:22 2016 Arnaud Boulay
*/

#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "malloc.h"

void		my_putstr(char *str)
{
  write(2, str, strlen(str));
}

void		my_putnbr_base(uint64_t nb, char *base)
{
  unsigned int	result;
  unsigned int	diviseur;
  unsigned int	size;

  size = strlen(base);
  if (size == 16)
    my_putstr("0x");
  diviseur = 1;
  while ((nb / diviseur) >= size)
    diviseur = diviseur * size;
  while (diviseur > 0)
    {
      result = (nb / diviseur) % size;
      write(2, &(base[result]), 1);
      diviseur = diviseur / size;
    }
}

void		my_putnbr(int nb)
{
  char		result;
  int		diviseur;

  diviseur = 1;
  while ((nb / diviseur) >= 10)
    diviseur = diviseur * 10;
  while (diviseur > 0)
    {
      result = (nb / diviseur) % 10 + 48;
      write(2, &result, 1);
      diviseur = diviseur / 10;
    }
}

void		aff_interval(t_block *tmp)
{
  my_putnbr_base((uint64_t)((void *)tmp + sizeof(t_block)), "0123456789ABCDEF");
  my_putstr(" - ");
  my_putnbr_base((uint64_t)((void *)tmp + tmp->size), "0123456789ABCDEF");
  my_putstr(" : ");
  my_putnbr(tmp->size - sizeof(t_block));
  my_putstr(" bytes\n");
}

void		show_alloc_mem()
{
  void		*addr;
  void		*end_address;
  t_block	*tmp;

  if (g_first_address == NULL)
    return ;
  end_address = sbrk(0);
  addr = g_first_address;
  my_putstr("break : ");
  my_putnbr_base((uint64_t)(end_address), "0123456789ABCDEF");
  my_putstr("\n");
  while (addr + sizeof(t_block) < end_address)
    {
      tmp = addr;
      if (tmp->magic_number == ALLOCATED_MAGIC_NUMBER)
	{
	  aff_interval(tmp);
	  if (tmp->size > 0)
	    addr += tmp->size;
	}
      else if (tmp->magic_number == FREE_MAGIC_NUMBER && tmp->size > 0)
	addr += tmp->size;
      else
	addr ++;
    }
}
