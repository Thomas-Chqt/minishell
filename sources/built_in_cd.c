/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:31:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/28 11:41:07 by hotph            ###   ########.fr       */
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
	if (exe->cmd_opts[1] == NULL)
		return (0);
	if (ft_access_wrap(exe->cmd_opts[1], ACCESS_FOK) == false)
		return (printf_error_msg("minishell: cd: %: No such file or directory",
				(exe->cmd_opts + 1), EX_FILE_OPEN_ERR));
	else if (ft_stat_wrap(exe->cmd_opts[1], STAT_ISDIR) == false)
		return (printf_error_msg("minishell: cd: %: Not a directory",
				(exe->cmd_opts + 1), EX_FILE_OPEN_ERR));
	else if (ft_access_wrap(exe->cmd_opts[1], ACCESS_XOK) == false)
		return (printf_error_msg("minishell: cd: %: Permission denied",
				(exe->cmd_opts + 1), EX_FILE_OPEN_ERR));
	return (0);
}

static int	set_env_key(char *key)
{
	char	*cwd;
	int		status;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (perror_wrap("minishell: cd: ", 1));
	status = set_env(key, cwd, true);
	free(cwd);
	if (status == MALLOC_ERROR)
		return (print_error(MALLOC_ERROR));
	else if (status == BAD_ENVIRONMENT_KEY)
		printf_error_msg("minshell: cd: %': not a\
valid identifier", &key, 1);
	return (status);
}

static int	cd_to_home(void)
{
	char	*path;
	int		status;

	path = get_env("HOME", NULL);
	status = 0;
	if (path == NULL)
		status = printf_error_msg("minishell: cd: HOME not set", NULL, 1);
	else if (*path == '\0')
		status = 0;
	else if (chdir(path) != 0)
		status = perror_wrap("minishell: cd: ", 1);
	free(path);
	return (status);
}

int	built_in_cd(t_exe *exe)
{
	int		status;
	char	*path;

	status = cd_check_path(exe);
	if (status != 0)
		return (return_or_exit(status, exe->flag_pipe));
	status = set_env_key("OLDPWD");
	if (status != 0)
		return (return_or_exit(status, exe->flag_pipe));
	if (exe->cmd_opts[1] == NULL)
		status = cd_to_home();
	else if (chdir(exe->cmd_opts[1]) != 0)
		status = perror_wrap("minishell: cd: ", 1);
	if (status != 0)
		return (return_or_exit(status, exe->flag_pipe));
	status = set_env_key("PWD");
	return (return_or_exit(status, exe->flag_pipe));
}
