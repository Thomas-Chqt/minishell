/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:52:12 by hotph             #+#    #+#             */
/*   Updated: 2023/08/28 11:43:13 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_temporary_name10(char *namespace, char *name, size_t size_space)
{
	static char	name_lotate;

	if (size_space < ft_strlen(name) + 1)
		return (NULL);
	ft_bzero(namespace, size_space);
	ft_memcpy(namespace, name, ft_strlen(name));
	if (name_lotate < '0' || '9' < name_lotate)
		name_lotate = '0';
	namespace[ft_strlen(name)] = name_lotate++;
	return (namespace);
}

void	putstr_to_fd(char *line, int *fd_out)
{
	if (*line == '\0')
		ft_putstr_fd("\n", *fd_out);
	else
		ft_putendl_fd(line, *fd_out);
}
