/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_print_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:50:34 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/04 18:05:42 by sotanaka         ###   ########.fr       */
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

	ft_printf("minishell: ");
	if (message == NULL)
	{
		ft_print_perror(cmd);
		exit(flag);
	}
	else
	{
		ft_printf("%s: %s\n", cmd, message);
		exit(flag);
	}
	exit (1);
}
