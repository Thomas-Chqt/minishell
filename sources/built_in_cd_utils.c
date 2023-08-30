/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:50:39 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/30 21:16:27 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*backwards_ptr(char *ptr, char *str_backwards, int len_str, int *i)
{
	while (*ptr)
	{
		if (ft_strncmp(ptr, str_backwards, len_str) != 0)
			break ;
		ptr += 3;
		*i += 1;
	}
	return (ptr);
}

void	curtail_str_by_char(char *str, char delim, int repeat)
{
	while (repeat-- > 0)
	{
		if (ft_strrchr(str, delim) == str)
			break ;
		*(ft_strrchr(str, delim)) = '\0';
	}
}

static int	cd_change_dir(char *path_dir, char *path_origin)
{
	int		status;

	status = set_env_key("OLDPWD");
	if (status != 0)
		;
	else if (path_dir != NULL && chdir(path_dir) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path_origin, STDERR_FILENO);
		status = perror_wrap(": ", 1);
	}
	else
		status = print_error(MALLOC_ERROR);
	return (status);
}

int	cd_via_upper(char *path)
{
	int		i;
	char	*cwd;
	char	*tmp;
	int		status;

	i = 0;
	path = backwards_ptr(path, "../", 3, &i);
	cwd = get_env("PWD", NULL);
	if (cwd == NULL)
		return (print_error(MALLOC_ERROR));
	curtail_str_by_char(cwd, '/', i);
	status = 0;
	tmp = ft_strjoin(cwd, "/");
	if (tmp == NULL)
		status = print_error(MALLOC_ERROR);
	free(cwd);
	if (status == 0)
	{
		cwd = ft_strjoin(tmp, path);
		status = cd_change_dir(cwd, &(path[i * (-3)]));
		free(cwd);
	}
	return (status);
}

int	cd_to_upper()
{
	char	*cwd;
	int		status;

	cwd = get_env("PWD", NULL);
	if (cwd == NULL)
		return (print_error(MALLOC_ERROR));
	status = set_env_key("OLDPWD");
	if (status != 0)
	{
		free(cwd);
		return (status);
	}
	curtail_str_by_char(cwd, '/', 1);
	if (chdir(cwd) != 0)
		status = perror_wrap("cd: ", 1);
	free(cwd);
	return (status);
}