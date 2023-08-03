/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:57:15 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/03 16:38:37 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_open_file(char *file_redirect, int flag_redirect, int fd_io)
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
	else
	{
		if (fd_io != fd && fd_io != STDIN_FILENO && fd_io != STDOUT_FILENO)
		{
			if (close(fd_io) == -1)
				exit(ft_print_perror("Error. Fail to close.\n"));
		}
	}
	return (fd);
}
