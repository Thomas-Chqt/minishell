/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:31:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/20 19:38:55 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "environment.h"

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

static int	set_env_pwd(void)
{
	char	*cwd;
	char	*key_val;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (perror_wrap("minishell: cd: ", 1));
	key_val = ft_calloc(ft_strlen(cwd) + 5, sizeof(char));
	if (key_val != NULL)
	{
		ft_strlcat(key_val, "PWD=", ft_strlen(cwd) + 5);
		ft_strlcat(key_val, cwd, ft_strlen(cwd) + 5);
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

	if (dexec->cmd_opts[1] != NULL && cd_check_path(dexec) == EX_FILE_OPEN_ERR)
	{
		if (dexec->flag_pipe == 0)
			return (1);
		exit (1);
	}
	status = 0;
	if (dexec->cmd_opts[1] == NULL)
	{
		path = get_env("HOME", NULL);
		if (chdir(path) != 0)
			status = perror_wrap("minishell: cd: ", 1);
		free(path);
	}
	else if (chdir(dexec->cmd_opts[1]) != 0)
		status = perror_wrap("minishell: cd: ", 1);
	status = set_env_pwd();
	if (dexec->flag_pipe == 0)
		return (status);
	exit(status);
}
