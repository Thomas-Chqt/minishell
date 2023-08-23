/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:52:27 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/23 09:48:57 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	built_in_pwd(t_exe *exe)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		exit (perror_wrap("minishell: cd: ", 1));
	ft_printf("%s\n", cwd);
	free(cwd);
	if (exe->flag_pipe == 0)
		return (0);
	exit (0);
}
