/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_check_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:08:29 by sotanaka          #+#    #+#             */
/*   Updated: 2023/07/31 19:24:58 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_cmdpath(t_dexec *dexec)
{
	int	err;

	errno = 0;
	err = access(dexec->cmd_path, F_OK);
	if (err == 0)
		return (0);
	// else
	// {
	// 	puts("no1");
	// 	return (ft_free_exec(dexec->matrix_envpath, NULL, dexec->cmd_path, 0));
	// }
	return (err);
}

int cmd_cant_use(char *cmd, t_dexec *dexec, int flag)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("minishell: ", cmd);
	if (tmp1 == NULL)
		return (ft_free_exec(dexec->matrix_envpath, NULL, NULL, 1));
	if (flag == CMD_SIMPLE)
	{
		ft_print_perror(tmp1);
		return (ft_free_exec(NULL, NULL, tmp1, 0));
	}
	else if (flag == CMD_NOTFOUND)
	{
		tmp2 = ft_strjoin(tmp1, ": command not found\n");
		if (tmp2 == NULL)
			return (ft_free_exec(dexec->matrix_envpath, NULL, tmp1, 1));
		ft_mes_error(tmp2);
		free(tmp1);
		return (ft_free_exec(dexec->matrix_envpath, NULL, tmp2, 0));
	}
	return (1);
}
