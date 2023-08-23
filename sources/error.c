/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:32:01 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/23 13:13:17 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	print_error_msg(char *msg, int return_val)
{
	ft_putendl_fd(msg, STDIN_FILENO);
	return (return_val);
}

int	print_error(int code)
{
	if (code == 0)
		return (0);
	if (code == MALLOC_ERROR)
		return (print_error_msg("minishell: Malloc error", code));
	if (code == PARSING_ERROR)
		return (print_error_msg("minishell: parsing error", SYNTAX_ERROR));
	if (code == MISSING_SQUOTE)
		return (print_error_msg("minishell: Missing quote `\'\'", SYNTAX_ERROR));
	if (code == MISSING_DQUOTE)
		return (print_error_msg("minishell: Missing quote `\"\'", SYNTAX_ERROR));
	if (code == MISSING_CLOSE_BRACKET)
	{
		ft_putstr_fd("minishell: Missing closing bracket `", STDERR_FILENO);
		ft_putchar_fd(125, STDERR_FILENO);
		return (print_error_msg("\'", SYNTAX_ERROR));
	}
	if (code == SIGACTION_ERROR)
		return (print_error_msg("minishell: Sigaction error", code));
	return (print_error_msg("minishell: Unknown error", code));
}

int	printf_error_msg(char *format, char *data[], int return_val)
{
	t_uint64	i;

	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			ft_putstr_fd(*(data++), STDERR_FILENO);
		else
			ft_putchar_fd(format[i], STDERR_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	return (return_val);
}

int	perror_wrap(char *msg, int val)
{
	perror(msg);
	return (val);
}
