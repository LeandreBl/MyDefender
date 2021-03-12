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

CC	= g++

LIB	:= -lm
LIB	+= -lsfml-graphics -lsfml-system -lsfml-network -lsfml-audio -lsfml-window
LIB	+= -lsfml-scene-static -lminiparsearg

STATIC_LIBS = MiniParseArg sfml-scene sfml-scene/build

SRC_DIR = src/

SOURCES = 	main.cpp				\
			DefenderSettings.cpp	\
			Wave.cpp				\
			FileParser.cpp			\
			MobWave.cpp				\

SRC	= $(addprefix $(SRC_DIR), $(SOURCES))

OBJ	= $(SRC:.cpp=.o)

RM	= rm -f

CXXFLAGS	= -I ./include
CXXFLAGS	+= $(addprefix -I ./, $(addsuffix /include, $(STATIC_LIBS)))
CXXFLAGS	+= -Wextra -Wall -std=c++2a

LDFLAGS += $(addprefix -L ./, $(STATIC_LIBS))

GREEN		= '\033[0;32m'
NO_COLOR	= '\033[0m'

%.o : %.cpp
	@$ $(CC) $(CXXFLAGS) -c $< -o $@
	@echo "$(CC) $(CXXFLAGS) -c $< -o $@ ["$(GREEN)"OK"$(NO_COLOR)"]"
.SUFFIXES: .o .cpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LIB) -o $(NAME)

dependencies:
	$(MAKE) -C MiniParseArg static

debug: CFLAGS += -g3
debug: re

opti: CFLAGS += -O3
opti: re

clean:
	$(RM) $(OBJ)
	$(MAKE) -C MiniParseArg clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C MiniParseArg fclean

re: fclean dependencies all

.PHONY: all clean fclean re
