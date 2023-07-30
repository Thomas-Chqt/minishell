/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:32:49 by sotanaka          #+#    #+#             */
/*   Updated: 2023/07/30 19:43:27 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <unistd.h>

// int	ft_exec(char *path, char *prog, char **cmd_opts); not adopt. i think its increase process.
int	ft_exec(char *cmd, char **cmd_opts, char **envp)
{
	t_dexec	dexec;
	t_pid	pid;

	if (ft_get_envpaths(envp, &dexec) == 1)
		return (1);
	if (ft_get_cmdpath(cmd, &dexec) == 1)
		return (1);
//comment out start
	for (size_t i = 0; dexec.matrix_envpath[i] != NULL ; i++)
	ft_printf("PATH = %s\n", dexec.matrix_envpath[i]);
	ft_printf("PATH COMMAND = %s\n", dexec.cmd_path);
//end
	pid = fork();
	if (pid == 0){

		if (execve(dexec.cmd_path, cmd_opts, envp) == -1)
		{
			if (errno != EACCES && errno != ENOENT)
				exit(ft_print_perror(dexec.cmd_path));
		}
	}

ft_free_exec(dexec.matrix_envpath, cmd_opts, dexec.cmd_path, 0);
return (0);
}

//comment out start
int main(int ac, char **av, char **envp)
{
	if (ac == 2)
		ft_exec(av[1], NULL, envp);
	if (ac == 3)
		ft_exec(av[1], ft_split(av[2], ' '), envp);
}
//end