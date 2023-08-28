/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:45:34 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/28 16:47:38 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int	print_envp(void);

int	built_in_env(int argc, char *argv[])
{
	t_uint64	i;

	if (argc == 1)
		return (print_envp());
	if (argv[1][0] == '-')
	{
		i = 1;
		while (argv[1][i] == '-')
			i++;
		if (argv[1][i] != '\0')
		{
			ft_putstr_fd("env: illegal option -- ", STDERR_FILENO);
			ft_putchar_fd(argv[1][i], STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			return (INPUT_ERROR);
		}
		return (0);
	}
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(argv[1], STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	return (NO_SUCH_FILE_DIR);
}

static int	print_envp(void)
{
	char		**envp;
	t_uint64	i;

	envp = get_envp();
	if (envp == NULL)
		return (print_error(MALLOC_ERROR));
	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		free(envp[i]);
		i++;
	}
	free(envp);
	return (0);
}
