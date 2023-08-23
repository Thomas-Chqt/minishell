# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/23 21:17:34 by tchoquet          #+#    #+#              #
#    Updated: 2023/08/29 11:42:05 by tchoquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT				= .
SRCS_DIR			= ${ROOT}/sources
INCLUDES_DIR		= ${ROOT}/includes
BUILD_DIR			= ${ROOT}/build
LIBFT_DIR			= ${ROOT}/Libft

SRC			= ${wildcard ${SRCS_DIR}/*.c}
OBJ			= ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${SRC:.c=.o}}

LIBFT			= ${LIBFT_DIR}/libft.a
LIBFT_MEMCHEK	= ${LIBFT_DIR}/libft_memcheck.a

CC						= cc
CFLAGS					= -Wall -Wextra -Werror
memcheck: CFLAGS 		+= -D MEMCHECK
EXTERNAL_LIBS			= -l readline
memcheck: EXTERNAL_LIBS += -l memory_leak_detector

NAME		= ${ROOT}/minishell


.PHONY: all memcheck clean fclean re 


all: ${NAME}

${NAME}: ${LIBFT} ${OBJ}
	@${CC} -o $@ $^ ${EXTERNAL_LIBS}
	@echo "Executable created at $@."


memcheck: ${LIBFT_MEMCHEK} ${OBJ}
	@${CC} -o ${NAME} $^ ${EXTERNAL_LIBS}
	@echo "Executable created at ${NAME}."


clean:
	@make -C ${LIBFT_DIR} clean
	@rm -rf ${BUILD_DIR}
	@echo "${BUILD_DIR} deleted. (minishell)"


fclean: clean
	@rm -rf ${LIBFT}
	@echo "${LIBFT} deleted."
	@rm -rf ${LIBFT_MEMCHEK}
	@echo "${LIBFT_MEMCHEK} deleted."
	@rm -rf ${LIBFT_DIR}/libft.h
	@echo "${LIBFT_DIR}/libft.h deleted."
	@rm -rf ${NAME}
	@echo "${NAME} deleted."


re: fclean all


${BUILD_DIR}/%.o: ${SRCS_DIR}/%.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${INCLUDES_DIR} -I${LIBFT_DIR}


#Libft
${LIBFT}:
	@make -C ${LIBFT_DIR} all

${LIBFT_MEMCHEK}:
	@make -C ${LIBFT_DIR} memcheck


#folders
${BUILD_DIR}:
	mkdir -p $@