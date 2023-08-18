/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:40:53 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/18 17:04:29 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	lstenv_clear(void);

int	init_env(char *envp[])
{
	t_uint64	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (set_env_single_str(envp[i], true) != 0)
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
	lstenv_clear();
}
