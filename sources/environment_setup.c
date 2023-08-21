/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:40:53 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/21 15:14:43 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	delete_entry(void *v_entry);

int	init_env(char *envp[])
{
	t_uint64	i;

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
	return (0);
}

void	clear_env(void)
{
	ft_lstclear((t_list **)get_lstenv(), &delete_entry);
}
