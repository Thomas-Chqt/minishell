/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:50:39 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/02 13:23:41 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cd_to_current(int flag_oldpwd)
{
	int		status;
	char	*cwd;

	status = get_pwd_wrap(&cwd);
	if (status != 0)
		return (status);
	if (flag_oldpwd == 0)
		status = set_env_key("OLDPWD");
	if (status == 0)
	{
		status = chdir(cwd);
		if (status != 0)
		{
			free(cwd);
			return (perror_wrap("cd: .", 1));
		}
	}
	free(cwd);
	return (status);
}

int	cd_via_upper(char *path, int flag_oldpwd)
{
	int	status;

	status = cd_to_upper(flag_oldpwd);
	if (status == 0)
		status = built_in_cd(&(path[3]), 0, flag_oldpwd + 1);
	return (status);
}

int	cd_to_upper(int flag_oldpwd)
{
	char	*cwd;
	int		status;

	status = get_pwd_wrap(&cwd);
	if (status != 0)
		return (status);
	if (flag_oldpwd == 0)
		status = set_env_key("OLDPWD");
	if (status == 0)
	{
		curtail_str_by_char(cwd, '/');
		if (chdir(cwd) != 0)
			status = perror_wrap("cd: ..", 1);
	}
	free(cwd);
	if (status != 0)
		return (status);
	return (set_env_key("PWD"));
}

int	cd_to_path(char *path, int flag_oldpwd)
{
	int	status;

	status = 0;
	if (flag_oldpwd == 0)
		status = set_env_key("OLDPWD");
	if (status != 0)
		return (status);
	if (chdir(path) != 0)
		status = perror_wrap("cd: ", 1);
	if (status != 0)
		return (status);
	return (set_env_key("PWD"));
}
