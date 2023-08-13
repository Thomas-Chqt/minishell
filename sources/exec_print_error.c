/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_print_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:50:34 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/13 12:06:28 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_mes_error(char *message)
{
	ft_putstr_fd (message, 2);
	return (EXIT_FAILURE);
}

int	ft_print_perror(char *original_message)
{
	perror(original_message);
	return (EXIT_FAILURE);
}

int	minishell_error(char *cmd, int flag, char *message)
{
	char	*tmp;

	ft_putstr_fd("minishell: ", 2);
	if (message == NULL)
	{
		ft_print_perror(cmd);
		return (flag);
	}
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(message, 2);
		return (flag);
	}
	return (flag);
}
