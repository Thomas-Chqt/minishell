/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:40:53 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/28 15:36:26 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	free_entry(void *v_entry);
char	**get_default_home_ptr(void);

int	init_env(char *envp[])
{
	t_uint64	i;
	int			error;

	i = 0;
	while (envp[i] != NULL)
	{
		if (set_env_single_str(envp[i], true) == MALLOC_ERROR)
		{
			clear_env();
			return (MALLOC_ERROR);
		}
		i++;
	}
	(*get_default_home_ptr()) = get_env("HOME", &error);
	if (error != 0)
	{
		clear_env();
		return (MALLOC_ERROR);
	}
	return (0);
}

void	clear_env(void)
{
	ft_lstclear((t_list **)get_lstenv(), &free_entry);
	free(*get_default_home_ptr());
}
