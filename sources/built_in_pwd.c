/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:52:27 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/21 11:33:16 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	built_in_pwd(t_dexec *dexec)
{
	int		exit_val;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		exit (perror_wrap("minishell: cd: ", 1));
	ft_printf("%s\n", cwd);
	free(cwd);
	if (dexec->flag_pipe == 0)
		return (exit_val);
	exit (exit_val);
}
