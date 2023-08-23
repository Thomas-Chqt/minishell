/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:09:39 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/23 13:13:02 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "environment.h"

static int	check_args(char *argv[]);

int	built_in_unset(int argc, char *argv[])
{
	t_uint64	i;

	if (argc <= 1)
		return (0);
	else
	{
		if (check_args(argv) != 0)
			return (2);
		i = 1;
		while (i < (t_uint64)argc)
		{
			if (delete_env(argv[i]) != 0)
				return (
					printf_error_msg("minshell: unset: `%': not a\
valid identifier", argv + i, 1));
			i++;
		}
	}
	return (0);
}

static int	check_args(char *argv[])
{
	if (argv[1][0] == '-' && argv[1][1] != '\0')
	{
		ft_putstr_fd("minshell: unset: -", STDERR_FILENO);
		ft_putchar_fd(argv[1][1], STDERR_FILENO);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		ft_putendl_fd("unset: usage: unset [name ...]", STDERR_FILENO);
		return (1);
	}
	return (0);
}
