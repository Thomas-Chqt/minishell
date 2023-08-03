/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_print_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:50:34 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/03 16:20:01 by sotanaka         ###   ########.fr       */
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

int	cmd_cant_use(char *cmd, int flag)
{
	char	*tmp;

	ft_printf("minishell: ");
	if (flag == CMD_SIMPLE || flag == CMD_PERM_DENIED || flag == IS_A_DIRECTORY)
	{
		ft_print_perror(cmd);
		exit(flag);
	}
	else if (flag == CMD_NOTFOUND)
	{
		ft_printf("%s: %s", cmd, ": command not found\n");
		exit(flag);
	}
	exit (1);
}
