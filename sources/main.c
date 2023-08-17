/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:27 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/17 00:43:22 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

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
	if (sig_interactive_mode() != 0)
		return (SIGACTION_ERROR);
	if (init_env(envp) != 0)
		return (1);
	minishell_loop();
	ft_printf("exit\n");
	clean_env();
	return (0);
}
