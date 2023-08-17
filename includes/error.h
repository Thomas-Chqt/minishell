/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:31:32 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/17 15:52:52 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

# define MALLOC_ERROR 1111
# define PARSING_ERROR 2222
# define MISSING_QUOTE 3333
# define MISSING_SQUOTE 4444
# define MISSING_DQUOTE 5555
# define MISSING_CLOSE_BRACKET 6666
# define BAD_SUBSTITUTION 7777
# define SYNTAX_ERROR 258
# define SIGACTION_ERROR 8888

int		print_error_msg(char *msg, int return_val);
int		print_error(int code);
int		printf_error_msg(char *format, char *data[], int return_val);
int		perror_wrap(char *msg, int val);
int		exec_error(char *cmd, int flag, char *msg);

#endif // ERROR_H