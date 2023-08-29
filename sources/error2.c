/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:16:27 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/28 17:34:09 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

static int	*current_line_ptr(void);
static char	**running_file_ptr(void);

void	set_current_line(int line_nbr)
{
	*(current_line_ptr()) = line_nbr;
}
void	set_running_file(char *file_name)
{
	*(running_file_ptr()) = file_name;
}

void	print_pre_error_msg(void)
{
	if (*(running_file_ptr()) == NULL)
		ft_putstr_fd("minishell: ", STDERR_FILENO);
	else
	{
		ft_putstr_fd(*(running_file_ptr()), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (*(current_line_ptr()))
	{
		ft_putstr_fd("line ", STDERR_FILENO);
		ft_putnbr_fd(*(current_line_ptr()), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
}

static int	*current_line_ptr(void)
{
	static int	current_line = 0;

	return (&current_line);
}

static char	**running_file_ptr(void)
{
	static char	*running_file = NULL;

	return (&running_file);
}
