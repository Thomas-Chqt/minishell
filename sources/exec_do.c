/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:32:49 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/02 22:01:49 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_exec_do_cmd(char *cmd_path, char **cmd_opts, char **envp)
{
	if (execve(cmd_path, cmd_opts, envp) == -1)
	{
		if (errno == EISDIR)
			cmd_cant_use(cmd_path, CMD_SIMPLE);
		exit(1);
	}
}

int	ft_exec_fork(char *path, char *prog, char **cmd_opts, char **envp)
{
	t_pid	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit(ft_print_perror("Error. Fail to fork.\n"));
	else if (pid == 0)
	{
		dexec.matrix_envpath =  ft_split_by_token(dexec.matrix_envpath, ':');
		dexec.cmd_path = ft_get_cmdpath(path, prog, &dexec);
		ft_exec_do_cmd(dexec.cmd_path, cmd_opts, envp);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}
