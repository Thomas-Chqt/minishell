/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_envpath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:12:27 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/07 19:09:43 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"

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
	free(tmp);
	return (matrix);
}
