/*
** main.c for unit-test in /home/danilo_d/Epitech-Projects/Semestre4/PSU_2015_malloc/tests
**
** Made by Danilov DImitri
** Login   <danilo_d@epitech.net>
**
** Started on Sat Feb 13 16:45:07 2016 Danilov DImitri
** Last update  Sat Feb 13 16:45:07 2016 Danilov DImitri
*/

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int		basic_tests()
{
  char		*test;

  printf("Test malloc(0)\n");
  test = malloc(0);
  printf("Test free 0\n");
  free(test);
  printf("test malloc(-1000)\n");
  test = malloc(-1000);
  printf("Test malloc(1000000)\n");
  test = malloc(1000000);
  free(test);
  printf("Test malloc(100)\n");
  test = malloc(100);
  printf("Test realloc to inferior\n");
  test = realloc(test, 10);
  printf("End testing basic tests , no errors !\n");
  return (0);
}

int		test_if_allocate_is_good(char *kappa, int size)
{
  int		i;

  i = 0;
  while (i < size)
    {
      kappa[i] = 123;
      i++;
    }
  return 0;
}

int		test_malloc(char *kappa, int nbr)
{
  int		random_free;

  kappa = malloc(nbr);
  test_if_allocate_is_good(kappa, nbr);
  random_free = random() % 2;
  if (random_free == 0)
    {
      free(kappa);
      return (1);
    }
  return (0);
}

int		main()
{
  int		i;
  int		nbr;
  char		*kappa;

  basic_tests();
  i = 0;
  srand(time(NULL));
  kappa = NULL;
  printf("start testing random malloc\n");
  while (i < 100000)
    {
      nbr = (random() % 5000) + 50;
      test_malloc(kappa, nbr);
      i++;
    }
  printf("Start testing growing number\n");
  i = 0;
  while (i < 10000)
    {
      test_malloc(kappa, i);
      i++;
    }
  printf("End testing !\n");
}
