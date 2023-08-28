/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:04:08 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/28 11:49:35 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "environment.h"

static void	print_entry(void *v_entry);
static int	check_args(char *argv[]);

int	built_in_export(int argc, char *argv[])
{
	t_uint64	i;
	int			temp_ret;
	int			error;

	error = 0;
	if (argc <= 1)
		ft_lstiter((t_list *)*(get_lstenv()), &print_entry);
	else
	{
		if (check_args(argv) != 0)
			return (2);
		i = 0;
		while (++i < (t_uint64)argc)
		{
			temp_ret = set_env_single_str(argv[i], true);
			if (temp_ret == NULL_ENVIRONMENT_VAL)
				temp_ret = export_env(argv[i]);
			if (temp_ret == BAD_ENVIRONMENT_KEY)
				error = printf_error_msg("minshell: export: `%': \
not a valid identifier", argv + i, 1);
			else if (temp_ret != 0)
				return (temp_ret);
		}
	}
	return (error);
}

static int	check_args(char *argv[])
{
	if (argv[1][0] == '-' && argv[1][1] != '\0')
	{
		ft_putstr_fd("minshell: export: -", STDERR_FILENO);
		ft_putchar_fd(argv[1][1], STDERR_FILENO);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		ft_putendl_fd("export: usage: export [name[=value] ...]",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}

static void	print_entry(void *v_entry)
{
	t_env_entry	*entry;

	entry = (t_env_entry *)v_entry;
	if (entry->is_export == true)
	{
		printf("declare -x %s", entry->key);
		if (entry->value != NULL)
			printf("=\"%s\"", entry->value);
		printf("\n");
	}
}
