/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:09:39 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/28 16:44:11 by tchoquet         ###   ########.fr       */
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
					printf_error_msg("unset: `%s': not a\
valid identifier", argv + i, 1));
			i++;
		}
	}
	return (0);
}

static int	check_args(char *argv[])
{
	if (argv[1][0] == '-' && argv[1][1] != '\0')
		return (printf_error_msg("unset: -%c: invalid option\nunset:  \
usage: unset [name ...]", (char *[1]){argv[1] + 1}, 1));
	return (0);
}
