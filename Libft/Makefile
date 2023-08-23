# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 11:15:20 by tchoquet          #+#    #+#              #
#    Updated: 2023/08/30 09:53:11 by tchoquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT				= .
SRCS_DIR			= ${ROOT}/sources
FT_PRINTF_SRC_DIR	= ${SRCS_DIR}/ft_printf_utils
INCLUDES_DIR		= ${ROOT}/includes
BUILD_DIR			= ${ROOT}/build

SRC	= ${wildcard ${SRCS_DIR}/*.c} ${wildcard ${FT_PRINTF_SRC_DIR}/*.c}
OBJ = ${patsubst ${SRCS_DIR}%, ${BUILD_DIR}%, ${patsubst ${FT_PRINTF_SRC_DIR}%, ${BUILD_DIR}%, ${SRC:.c=.o}}}

CC					= cc
CFLAGS				= -Wall -Wextra -Werror
memcheck: CFLAGS 	+= -D MEMCHECK

NAME			= ${ROOT}/libft.a
NAME_MEMCHEK	= ${ROOT}/libft_memcheck.a
EXPORT_INCLUDE	= ${ROOT}/libft.h


.PHONY: all clean fclean re memcheck


all: ${NAME} ${EXPORT_INCLUDE}

${NAME}: ${OBJ}
	@ar rc $@ $^
	@echo "Archive created at $@."


memcheck: ${NAME_MEMCHEK} ${EXPORT_INCLUDE}

${NAME_MEMCHEK}: ${OBJ}
	@ar rc $@ $^
	@echo "Archive created at $@."


clean:
	@rm -rf ${BUILD_DIR}
	@echo "${BUILD_DIR} deleted. (Libft)"


fclean: clean
	@rm -rf ${NAME}
	@echo "${NAME} deleted."
	@rm -rf ${EXPORT_INCLUDE}
	@echo "${EXPORT_INCLUDE} deleted."


re: fclean all


${BUILD_DIR}/%.o: ${SRCS_DIR}/%.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${INCLUDES_DIR}

${BUILD_DIR}/%.o: ${FT_PRINTF_SRC_DIR}/%.c | ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $< -I${INCLUDES_DIR}

${ROOT}/%.h: ${INCLUDES_DIR}/%.h
	cp $< $@


#folders
${BUILD_DIR}:
	mkdir -p $@