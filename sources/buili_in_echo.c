/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buili_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:46:23 by hotph             #+#    #+#             */
/*   Updated: 2023/08/18 12:27:33 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	echo_do_at_child(t_dexec *dexec)
{
	int		exit_val;
	int		i;
	int		n_flag;

	exit_val = set_redirect(dexec);
	if (exit_val != 0)
		exit(exit_val);
	i = 1;
	n_flag = 0;
	if (dexec->cmd_opts[i] && str_cmp(dexec->cmd_opts[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (dexec->cmd_opts[i])
	{
		ft_putstr_fd(dexec->cmd_opts[i], STDOUT_FILENO);
		if (dexec->cmd_opts[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	exit (exit_val);
}

int	built_in_echo(t_dexec *dexec)
{
	t_pid	pid;

	pid = fork();
	if (pid == -1)
		return (perror_wrap("fork", -1));
	if (pid == 0)
		echo_do_at_child(dexec);
	else
		return (pid);
	return (0);
}
