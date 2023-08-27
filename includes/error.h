/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:31:32 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/24 17:02:42 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

# define SYNTAX_ERROR 258
# define INPUT_ERROR 1
# define NO_SUCH_FILE_DIR 127

# define MALLOC_ERROR 1111
# define PARSING_ERROR 2222
# define MISSING_SQUOTE 4444
# define MISSING_DQUOTE 5555
# define MISSING_CLOSE_BRACKET 6666
# define BAD_SUBSTITUTION 7777
# define SIGACTION_ERROR 8888
# define BAD_ENVIRONMENT_KEY 9999
# define NULL_ENVIRONMENT_VAL 1010

int		print_error_msg(char *msg, int return_val);
int		print_error(int code);
int		printf_error_msg(char *format, char *data[], int return_val);
int		perror_wrap(char *msg, int val);

#endif // ERROR_H