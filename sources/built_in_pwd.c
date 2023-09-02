/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:52:27 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/31 18:35:29 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	built_in_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL && errno == EACCES)
	{
		cwd = get_env("PWD", NULL);
		if (cwd == NULL)
			return (perror_wrap("pwd: ", 1));
		ft_putendl_fd(cwd, STDOUT_FILENO);
	}
	else if (cwd == NULL)
		return (perror_wrap("pwd: ", 1));
	else
		ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
}
