/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_get_envpath.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:12:27 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/01 18:54:19 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_get_envpaths(char **envp, t_dexec *dexec)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			dexec->matrix_envpath = ft_split(&envp[i][5], ':');
			if (dexec->matrix_envpath == NULL)
			{
				ft_mes_error("Error. Fail allocate memory.\n");
				exit(1);
			}
			return (0);
		}
		i++;
	}
	ft_mes_error("Error: PATH= not found.");
	exit (1);
}
