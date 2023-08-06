/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:27 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/06 15:53:55 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef MEMCHECK

__attribute__((destructor))
static void	destructor(void)
{
	char	*pid;
	char	*cmd;

	print_report();
	pid = ft_itoa(getpid());
	cmd = ft_strjoin("leaks -q ", pid);
	system((const char *)cmd);
	free(pid);
	free(cmd);
}

#endif // MEMCHECK

int	main(int argc, char *argv[], char *envp[])
{
	char		*cmd;

	if (argc || argv)
		argc = (int)argv;
	if (init_env(envp) != 0)
		return (1);
	while (1)
	{
		cmd = readline("minishell > ");
		if (cmd == NULL || cmd[0] == '\0')
		{
			free(cmd);
			continue ;
		}
		add_history(cmd);
		if (str_cmp(cmd, "exit") == 0)
		{
			free(cmd);
			break ;
		}
		free(cmd);
	}
	clean_env();
	return (0);
}
