/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_get_envpath.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:12:27 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/02 14:18:08 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_get_envpaths(char **envp, t_dexec *dexec)
{
	size_t	i;
	char	*tmp;

	tmp = get_env("PATH");
	if (tmp == NULL)
		return (ft_mes_error("Error: 'PATH' not found."));
	dexec->matrix_envpath = ft_split(tmp, ':');
	if (dexec->matrix_envpath == NULL)
		exit(ft_mes_error("Error. Fail allocate memory.\n"));
	return (0);
}
