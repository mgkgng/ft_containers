SRCS =	srcs/test.cpp

OBJS =	${SRCS:.cpp=.o}

NAME = containers

INCLUDES = ./includes/

CFLAG = -Wextra -Wall -Werror

CPPFLAG = -std=c++98

GREEN	:= "\033[0m\033[1;32m"
CYAN	:= "\033[0m\033[1;36m"
RESET	:= "\033[0m"


all:	${NAME}

%.o:	%.cpp
		@printf ${GREEN}"\r\033[KCompiling objects... "${RESET}"⏳"
		@clang++ ${CFLAGS} ${CPPFLAG} -I${INCLUDES} -c $< -o $@

${NAME}:	${OBJS}
			@clang++ ${CFLAGS} ${CPPFLAG} -I${INCLUDES} -o ${NAME} ${OBJS}

clean:
		@rm -rf ${OBJS}

fclean:	clean
		@rm -rf ${NAME}

re:	fclean all

.PHONY:	all clean fclean re