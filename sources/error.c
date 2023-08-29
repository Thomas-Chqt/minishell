/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:32:01 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/28 17:55:01 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	print_pre_error_msg(void);

int	print_error_msg(char *msg, int return_val)
{		
	print_pre_error_msg();
	ft_putendl_fd(msg, STDIN_FILENO);
	return (return_val);
}

int	print_error(int code)
{
	if (code == 0)
		return (0);
	if (code == MALLOC_ERROR)
		return (print_error_msg("Malloc error", code));
	if (code == PARSING_ERROR)
		return (print_error_msg("parsing error", SYNTAX_ERROR));
	if (code == MISSING_SQUOTE)
		return (print_error_msg("Missing quote `\'\'", SYNTAX_ERROR));
	if (code == MISSING_DQUOTE)
		return (print_error_msg("Missing quote `\"\'", SYNTAX_ERROR));
	if (code == MISSING_CLOSE_BRACKET)
		return (print_error_msg("Missing closing bracket `}\'", SYNTAX_ERROR));
	if (code == SIGACTION_ERROR)
		return (print_error_msg("Sigaction error", code));
	return (print_error_msg("Unknown error", code));
}

int	printf_error_msg(char *format, char *data[], int return_val)
{
	t_uint64	i;

	i = 0;
	print_pre_error_msg();
	while (format[i] != '\0')
	{
		if (ft_strncmp(format + i, "%s", 2) == 0)
		{
			ft_putstr_fd(*(data++), STDERR_FILENO);
			i++;
		}
		else if (ft_strncmp(format + i, "%c", 2) == 0)
		{
			write(STDERR_FILENO, *(data++), 1);
			i++;
		}
		else
			ft_putchar_fd(format[i], STDERR_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	return (return_val);
}

int	perror_wrap(char *msg, int val)
{
	print_pre_error_msg();
	perror(msg);
	return (val);
}
