SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
INCLUDES = includes/*.hpp
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
NAME = containers

.cpp.o:
	${CC} ${FLAGS} -c $< -o ${<:.cpp=.o}

all: ${NAME}

${NAME}: ${OBJS} ${INCLUDES}
	rm -rf .vscode
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re : fclean all
