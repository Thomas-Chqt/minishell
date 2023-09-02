/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:31:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/02 13:29:47 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	return_or_exit(int val, int flag)
{
	if (flag == 0)
		return (val);
	exit(val);
}

static int	cd_check_path(char *path, char *origin_path)
{
	if (path == NULL || path[0] == '\0')
		return (0);
	if (ft_access_wrap(path, ACCESS_FOK) == false)
		return (printf_error_msg("cd: %s: No such file or directory",
				&origin_path, EX_FILE_OPEN_ERR));
	else if (ft_access_wrap(path, ACCESS_XOK) == false)
		return (printf_error_msg("cd: %s: Permission denied",
				&origin_path, EX_FILE_OPEN_ERR));
	else if (ft_stat_wrap(path, STAT_ISDIR) == false)
		return (printf_error_msg("cd: %s: Not a directory",
				&origin_path, EX_FILE_OPEN_ERR));
	return (0);
}

int	set_env_key(char *key)
{
	char	*cwd;
	int		status;

	status = 0;
	if (str_cmp(key, "OLDPWD") == 0)
		status = get_pwd_wrap(&cwd);
	else
		cwd = getcwd(NULL, 0);
	if (cwd == NULL && status == 0)
		return (perror_wrap("cd: ", 1));
	else if (status != 0)
		return (status);
	status = set_env(key, cwd, true);
	free(cwd);
	if (status == MALLOC_ERROR)
		return (print_error(MALLOC_ERROR));
	else if (status == BAD_ENVIRONMENT_KEY)
		printf_error_msg("cd: `%s': not a valid identifier", &key, 1);
	return (status);
}

static int	cd_to_home(void)
{
	char	*path;
	int		status;

	status = 0;
	path = get_env("HOME", NULL);
	if (path == NULL)
		return (printf_error_msg("cd: HOME not set", NULL, 1));
	else if (*path == '\0')
		status = 0;
	else
	{
		status = set_env_key("OLDPWD");
		if (status != 0)
		{
			free(path);
			return (status);
		}
		if (chdir(path) != 0)
			status = perror_wrap("cd: ", 1);
	}
	free(path);
	if (status != 0)
		return (status);
	return (set_env_key("PWD"));
}

int	built_in_cd(char *path, int flag_pipe, int flag_oldpwd)
{
	int		status;

	if (path != NULL && *path == '\0')
		return (0);
	if (path == NULL || path[0] == '\0')
		status = cd_to_home();
	else if (str_cmp(path, ".") == 0)
		status = cd_to_current(flag_oldpwd);
	else if (str_cmp(path, "..") == 0 || str_cmp(path, "../") == 0)
		status = cd_to_upper(flag_oldpwd);
	else
	{
		status = cd_check_path(path, &path[(flag_oldpwd * (-3))]);
		if (status != 0)
			return (return_or_exit(status, flag_pipe));
		else if (ft_strncmp("../", path, 3) == 0)
			status = cd_via_upper(path, flag_oldpwd);
		else
			status = cd_to_path(path, flag_oldpwd);
	}
	return (return_or_exit(status, flag_pipe));
}
