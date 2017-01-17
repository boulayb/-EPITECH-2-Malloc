/*
** malloc.h for malloc in /home/danilo_d/Epitech-Projects/Semestre4/Malloc-working
**
** Made by Danilov DImitri
** Login   <danilo_d@epitech.net>
**
** Started on Thu Feb 11 09:50:25 2016 Danilov DImitri
** Last update Sun Feb 14 19:58:11 2016 Arnaud Boulay
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# define FREE_MAGIC_NUMBER	0x6837e70e
# define ALLOCATED_MAGIC_NUMBER	0x7834943e
# define NUMBER_INTERVALS	15

# include <stdlib.h>

typedef struct			s_block
{
  size_t			size;
  struct s_block		*next;
  struct s_block		*back;
  int				magic_number;
  int				*footer_size;
}				t_block;

typedef struct			s_table
{
  int				intervals;
  t_block			*table[NUMBER_INTERVALS];
}				t_table;

extern pthread_mutex_t		g_lock;
extern t_table			*g_free_table;
extern void			*g_first_address;

int				add_to_free_list(t_block *block,
						 int hashed_size);
int				hash_size_list(size_t size);
int				create_free_table(size_t);
void				change_table(t_block *block);
void				show_alloc_mem();
void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				*calloc(size_t nmemb, size_t size);
t_block				*find_free_space_table(size_t size);

#endif /* !MALLOC_H_ */
