/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:31:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/21 14:27:58 by sotanaka         ###   ########.fr       */
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

static int	cd_check_path(t_dexec *dexec)
{
	if (ft_access_wrap(dexec->cmd_opts[1], ACCESS_FOK) == false)
		return (printf_error_msg("minishell: cd: %: No such file or directory",
				(dexec->cmd_opts + 1), EX_FILE_OPEN_ERR));
	else if (ft_stat_wrap(dexec->cmd_opts[1], STAT_ISDIR) == false)
		return (printf_error_msg("minishell: cd: %: Not a directory",
				(dexec->cmd_opts + 1), EX_FILE_OPEN_ERR));
	else if (ft_access_wrap(dexec->cmd_opts[1], ACCESS_XOK) == false)
		return (printf_error_msg("minishell: cd: %: Permission denied",
				(dexec->cmd_opts + 1), EX_FILE_OPEN_ERR));
	return (0);
}

static int	set_env_key(char *key)
{
	char	*cwd;
	char	*key_val;
	int		len_key;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (perror_wrap("minishell: cd: ", 1));
	len_key = ft_strlen(key);
	key_val = ft_calloc(ft_strlen(cwd) + len_key + 1, sizeof(char));
	if (key_val != NULL)
	{
		ft_strlcat(key_val, key, ft_strlen(cwd) + len_key + 1);
		ft_strlcat(key_val, cwd, ft_strlen(cwd) + len_key + 1);
		if (set_env_single_str(key_val, false) == 0)
		{
			free(key_val);
			free(cwd);
			return (0);
		}
		free(key_val);
	}
	free(cwd);
	return (print_error(MALLOC_ERROR));
}

int	built_in_cd(t_dexec *dexec)
{
	int		status;
	char	*path;

	status = cd_check_path(dexec);
	if (status != 0)
		return (return_or_exit(status, dexec->flag_pipe));
	status = set_env_key("OLDPWD=");
	if (status != 0)
		return (return_or_exit(status, dexec->flag_pipe));
	if (dexec->cmd_opts[1] == NULL)
	{
		path = get_env("HOME", NULL);
		if (chdir(path) != 0)
			status = perror_wrap("minishell: cd: ", 1);
		free(path);
	}
	else if (chdir(dexec->cmd_opts[1]) != 0)
		status = perror_wrap("minishell: cd: ", 1);
	if (status != 0)
		return (return_or_exit(status, dexec->flag_pipe));
	status = set_env_key("PWD=");
		return (return_or_exit(status, dexec->flag_pipe));
}
