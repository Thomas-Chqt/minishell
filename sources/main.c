/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:27 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/18 17:16:26 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

#include "environment.h"

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
		return (print_error(SIGACTION_ERROR));
	if (init_env(envp) != 0)
		return (MALLOC_ERROR);
	minishell_loop();
	ft_printf("exit\n");
	clear_env();
	return (0);
}
