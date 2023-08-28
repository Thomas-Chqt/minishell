/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:31:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/28 19:03:03 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "environment.h"

static int	return_or_exit(int val, int flag)
{
	if (flag == 0)
		return (val);
	exit(val);
}

static int	cd_check_path(t_exe *exe)
{
	if (exe->cmd_opts[1] == NULL || exe->cmd_opts[1][0] == '\0')
		return (0);
	if (ft_access_wrap(exe->cmd_opts[1], ACCESS_FOK) == false)
		return (printf_error_msg("cd: %s: No such file or directory",
				(exe->cmd_opts + 1), EX_FILE_OPEN_ERR));
	else if (ft_stat_wrap(exe->cmd_opts[1], STAT_ISDIR) == false)
		return (printf_error_msg("cd: %s: Not a directory",
				(exe->cmd_opts + 1), EX_FILE_OPEN_ERR));
	else if (ft_access_wrap(exe->cmd_opts[1], ACCESS_XOK) == false)
		return (printf_error_msg("cd: %s: Permission denied",
				(exe->cmd_opts + 1), EX_FILE_OPEN_ERR));
	return (0);
}

static int	set_env_key(char *key)
{
	char	*cwd;
	int		status;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (perror_wrap("cd: ", 1));
	status = set_env(key, cwd, true);
	free(cwd);
	if (status == MALLOC_ERROR)
		return (print_error(MALLOC_ERROR));
	else if (status == BAD_ENVIRONMENT_KEY)
		printf_error_msg("cd: `%s': not a valid identifier", &key, 1);
	return (status);
}

static int	cd_to_home(char *cmd_opts, int flag_pipe)
{
	char	*path;
	int		status;

	if (cmd_opts != NULL && *cmd_opts == '\0')
		return (0);
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
			return (return_or_exit(status, flag_pipe));
		if (chdir(path) != 0)
			status = perror_wrap("cd: ", 1);
	}
	free(path);
	return (status);
}

int	built_in_cd(t_exe *exe)
{
	int		status;

	status = cd_check_path(exe);
	if (status != 0)
		return (return_or_exit(status, exe->flag_pipe));
	if (exe->cmd_opts[1] == NULL || exe->cmd_opts[1][0] == '\0')
		status = cd_to_home(exe->cmd_opts[1], exe->flag_pipe);
	else
	{
		status = set_env_key("OLDPWD");
		if (status != 0)
			return (return_or_exit(status, exe->flag_pipe));
		if (chdir(exe->cmd_opts[1]) != 0)
			status = perror_wrap("cd: ", 1);
	}
	if (status != 0)
		return (return_or_exit(status, exe->flag_pipe));
	status = set_env_key("PWD");
	return (return_or_exit(status, exe->flag_pipe));
}
