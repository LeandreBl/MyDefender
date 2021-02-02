##
## Makefile for *** in /home/leandre/***
##
## Made by Léandre Blanchard
## Login   <leandre.blanchard@epitech.eu>
##
## Started on  Thu Dec 15 20:24:11 2016 Léandre Blanchard
## Last update Sat Jan  6 19:05:29 2018 Léandre Blanchard
##

NAME	= my_defender

CC	= gcc

LIB	+= -lm
LIB	+= -lcsfml-graphics -lcsfml-system -lcsfml-network -lcsfml-audio -lcsfml-window
LIB	+= -llscene -llargs -llbl-libc

STATIC_LIBS = lvector arguments-handler csfml-scene Custom-libc

SRC_DIR = src/

SOURCES = 	main.c 				\
			argument_handlers.c	\
			config_file.c		\
			mob_config.c		\
			mob.c				\
			wave_config.c		\
			mob_wave.c			\
			utils.c				\
			my_defender.c

SRCS	= $(addprefix $(SRC_DIR), $(SOURCES))

OBJ	= $(SRCS:.c=.o)

RM	= rm -f

CPPFLAGS	+= $(addprefix -I ./, $(STATIC_LIBS))

CFLAGS	= -I ./include
CFLAGS	+= -Wextra -Wall -std=gnu11

GREEN		= '\033[0;32m'
NO_COLOR	= '\033[0m'

%.o : %.c
	@$ $(CC) $(CFLAGS) -c $< -o $@
	@echo "$(CC) $(CFLAGS) -c $< -o $@ ["$(GREEN)"OK"$(NO_COLOR)"]"
.SUFFIXES: .o .c

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIB) -o $(NAME)

dependencies:
	@git submodule foreach make static

debug: CFLAGS += -g3
debug: re

opti: CFLAGS += -O3
opti: re

clean:
	$(RM) $(OBJ)
	@git submodule foreach make clean

fclean: clean
	$(RM) $(NAME)
	@git submodule foreach make fclean

re: fclean all

.PHONY: all clean fclean re
