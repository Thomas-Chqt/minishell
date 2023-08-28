/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 23:03:15 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/28 11:16:15 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "environment.h"

void	sigint_handler_new_line(int sig)
{
	(void)sig;
	set_last_error(1);
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_putstr_fd("\033[0;31m✘\033[0m ", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sig_forwarding(int sig)
{
	if (sig == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}

void	sigint_handler_exit(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_DFL);
	kill(0, SIGINT);
}
