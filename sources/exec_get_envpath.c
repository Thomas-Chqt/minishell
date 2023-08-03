/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_get_envpath.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:12:27 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/02 15:04:07 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**ft_split_by_token(char **matrix, char token)
{
	size_t	i;
	char	*tmp;

	tmp = get_env("PATH");
	if (tmp == NULL)
		exit (ft_mes_error("Error: 'PATH' not found."));
	matrix = ft_split(tmp, token);
	if (matrix == NULL)
		exit(ft_mes_error("Error. Fail allocate memory.\n"));
	return (matrix);
}
