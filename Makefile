##
## Makefile for malloc in /home/boulay_b/Rendu/SE4/PSU/PSU_2015_malloc
##
## Made by Arnaud Boulay
## Login   <boulay_b@epitech.net>
##
## Started on  Thu Jan 28 10:06:27 2016 Arnaud Boulay
## Last update Sun Feb 14 19:28:54 2016 Arnaud Boulay
##

NAME	= libmy_malloc.so

RM	= rm -rf

GCC	= gcc -o

SRCFO	= sources/

SRCS	= $(SRCFO)malloc.c \
	  $(SRCFO)table.c \
	  $(SRCFO)free.c \
	  $(SRCFO)realloc.c \
	  $(SRCFO)calloc.c \
	  $(SRCFO)hash.c \
	  $(SRCFO)show_mem.c

OBJS	= $(SRCS:.c=.o)

CFLAGS	+= -Iincludes/ -Wall -Wextra -Werror -fPIC
LDFLAGS	+= -shared

all: $(NAME)

$(NAME): $(OBJS)
	 $(GCC) $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS)

debug: CFLAGS = -Iincludes/ -Wall -Wextra -g3 -fPIC
debug: all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re debug
