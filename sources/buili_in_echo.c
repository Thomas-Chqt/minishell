/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buili_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:46:23 by hotph             #+#    #+#             */
/*   Updated: 2023/08/21 11:47:32 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	echo_print(char **cmd_opts, int i)
{
	while (cmd_opts[i])
	{
		ft_putstr_fd(cmd_opts[i], STDOUT_FILENO);
		if (cmd_opts[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
}

int	built_in_echo(t_dexec *dexec)
{
	int		exit_val;
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	exit_val = 0;
	if (dexec->cmd_opts[i] && str_cmp(dexec->cmd_opts[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	echo_print(dexec->cmd_opts, i);
	if (n_flag == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (dexec->flag_pipe == 0)
		return (exit_val);
	exit (exit_val);
}
