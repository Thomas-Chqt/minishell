/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:45:34 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/06 15:51:08 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	print_entry_env(void *v_entry);
static void	print_entry_export(void *v_entry);

int	env(int argc, char *argv[])
{
	t_uint64	i;

	if (argc <= 1)
	{
		ft_lstiter((t_list *)*(get_lstenv()), &print_entry_env);
		return (0);
	}
	if (argv[1][0] == '-')
	{
		i = 1;
		while (argv[1][i] == '-')
			i++;
		if (argv[1][i] != '\0')
			ft_printf("env: illegal option -- %c", argv[1][i]);
	}
	else
		ft_printf("env: %s: No such file or directory", argv[1]);
	return (1);
}

int	export(int argc, char *argv[])
{
	t_uint64	i;

	if (argc <= 1)
	{
		ft_lstiter((t_list *)*(get_lstenv()), &print_entry_export);
		return (0);
	}
	i = 1;
	while (i < (t_uint64)argc)
	{
		if (set_env2(argv[i], true) != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	print_entry_env(void *v_entry)
{
	t_env_entry	*entry;

	entry = (t_env_entry *)v_entry;
	if (entry->is_export == true && entry->value != NULL)
		ft_printf("%s=%s\n", entry->key, entry->value);
}

static void	print_entry_export(void *v_entry)
{
	t_env_entry	*entry;

	entry = (t_env_entry *)v_entry;
	if (entry->is_export == true)
	{
		ft_printf("declare -x %s", entry->key);
		if (entry->value != NULL)
			ft_printf("=\"%s\"", entry->value);
		ft_printf("\n");
	}
}
