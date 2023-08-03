/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_open_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:57:15 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/02 22:08:39 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_open_file(char *file_redirect, int flag_redirect)
{
	int	fd;

	if (flag_redirect == GREAT)
		fd = open(file_redirect, O_WRONLY | O_CREAT | O_TRUNC);
	else if (flag_redirect == DGREAT)
		fd = open(file_redirect, O_WRONLY | O_CREAT | O_APPEND);
	else
		fd = open(file_redirect, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("minishell: ");
		ft_print_perror(file_redirect);
		exit (EX_FILE_OPEN_ERR);
	}
	return (fd);
}
