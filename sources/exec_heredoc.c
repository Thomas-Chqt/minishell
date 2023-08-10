/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:00:16 by hotph             #+#    #+#             */
/*   Updated: 2023/08/10 15:30:49 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_readline(int fd_pipe[2], char *delimiter)
{
	char	*line;

	if (close(fd_pipe[0]) == -1)
		exit(ft_print_perror("Error. Fail to close pipe[0]_readline\n"));
	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = readline("");
		if (line == NULL)
			break ;
		if (str_cmp(line, delimiter) == 0)
		{
			free(line);
			if (close(fd_pipe[1]) == -1)
				exit(ft_print_perror("Error. Fail to close pipe[1]_readline\n"));
			break ;
		}
		ft_putstr_fd(line, fd_pipe[1]);
		ft_putstr_fd("\n", fd_pipe[1]);
		free(line);
	}
	exit(0);
}

int	ft_here_doc(char *delimiter, int fd_in)
{
	int		fd_pipe[2];
	int		pid;
	char	*line;

	if (fd_in > 0)
	{
		if (close(fd_in) == -1)
			exit(ft_print_perror("Error. Fail to close fd_in.\n"));
	}
	if (pipe(fd_pipe) == -1)
		exit(ft_print_perror("Error. Fail to create pipe.\n"));
	pid = fork();
	if (pid == -1)
		exit(ft_print_perror("Error. Fail to fork.\n"));
	if (pid == 0)
		ft_readline(fd_pipe, delimiter);
	else
	{
		waitpid(pid, NULL, 0);
		if (close(fd_pipe[1]) == -1)
			exit(ft_print_perror("Error. Fail to close pipe[1].\n"));
	}
	return (fd_pipe[0]);
}
