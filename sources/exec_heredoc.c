/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:24:07 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/24 20:13:12 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_temporary_name10(char *namespace, char *name, int size_space)
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

static int	ft_readline(int *fd_tmphere, char *delimiter)
{
	char	*line;

	if (sig_heredoc_mode() != 0)
		return (print_error(SIGACTION_ERROR));
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (str_cmp(line, delimiter) == 0)
		{
			free(line);
			if (close(*fd_tmphere) == -1)
				exit(perror_wrap("readline", 1));
			break ;
		}
		ft_putstr_fd(line, *fd_tmphere);
		ft_putstr_fd("\n", *fd_tmphere);
		free(line);
	}
	exit(0);
}

int	ft_here_doc(char *delimiter, int *fd_in)
{
	int		pid;
	int		status;
	char	filename[15];

	if (sig_heredoc_parent_mode() != 0)
		return (print_error(SIGACTION_ERROR));
	if (ft_open_file(get_temporary_name10
			(filename, ".TMPminishell", 15), GREAT, fd_in) == 1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (perror_wrap("here_doc fork", 1));
	if (pid == 0)
		ft_readline(fd_in, delimiter);
	else
	{
		if (waitpid(pid, &status, 0) == -1 || sig_forwarding_mode() != 0)
			return (perror_wrap("here_doc", 1));
		if (ft_open_file(filename, LESS, fd_in) == 1)
			return (1);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}
