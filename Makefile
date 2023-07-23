# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/23 21:17:34 by tchoquet          #+#    #+#              #
#    Updated: 2023/07/23 23:28:02 by tchoquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT			= .
SRCS_DIR		= ${ROOT}/sources
INCLUDES_DIR 	= ${ROOT}/includes
BUILD_DIR		= ${ROOT}/.build

SRC			= ${wildcard ${SRCS_DIR}/*.c}
OBJ			= ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${SRC:.c=.o}}
OBJ_DEBUG	= ${OBJ:.o=_debug.o}

CC						= gcc
CFLAGS					= -Wall -Wextra -Werror
debug: CFLAGS			= -g -D MEMCHECK
EXTERNAL_LIBS			= -l ft -l readline
debug: EXTERNAL_LIBS	= -l ft_debug -l memory_leak_detector -l readline


NAME		= ${ROOT}/minishell
NAME_DEBUG	= ${ROOT}/minishell_debug


.PHONY: all clean fclean re debug cleandebug fcleandebug redebug norm cleanbuild


all: ${NAME}

${NAME}: ${OBJ}
	@${CC} -o $@ $^ ${EXTERNAL_LIBS}
	@echo "Executable created at $@."

clean:
	@rm -rf ${OBJ}
	@echo "Release object files in ${BUILD_DIR} deleted."

fclean: clean
	@rm -rf ${NAME}
	@echo "${NAME} deleted."

re: fclean all




debug: ${NAME_DEBUG}

${NAME_DEBUG}: ${OBJ_DEBUG}
	@${CC} -o $@ $^ ${EXTERNAL_LIBS}
	@echo "Executable created at $@."

cleandebug:
	@rm -rf ${OBJ_DEBUG}
	@echo "Debug object files in ${BUILD_DIR} deleted."

fcleandebug: cleandebug
	@rm -rf ${NAME_DEBUG}
	@echo "${NAME_DEBUG} deleted."

redebug: fcleandebug debug




norm:
	@norminette ${SRCS_DIR} ${INCLUDES_DIR}


cleanbuild:
	@rm -rf ${BUILD_DIR}
	@echo "Build folder deleted."



${BUILD_DIR}/%_debug.o ${BUILD_DIR}/%.o: ${SRCS_DIR}/%.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${INCLUDES_DIR}


#folders
${BUILD_DIR}:
	mkdir -p $@