/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:52:27 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/19 14:00:31 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	pwd_do_at_child(t_dexec *dexec)
{
	int		exit_val;
	char	*cwd;

	exit_val = set_redirect(dexec);
	if (exit_val != 0)
		exit(exit_val);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		exit (perror_wrap("minishell: cd: ", 1));
	ft_printf("%s\n", cwd);
	free(cwd);
	exit (exit_val);
}

int	built_in_pwd(t_dexec *dexec)
{
	t_pid	pid;

	pid = fork();
	if (pid == -1)
		return (perror_wrap("fork", -1));
	if (pid == 0)
		pwd_do_at_child(dexec);
	else
		return (pid);
	return (0);
}