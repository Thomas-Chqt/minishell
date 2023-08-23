/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 23:03:15 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/23 13:20:06 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "environment.h"

void	sigint_handler_new_line(int sig)
{
	(void)sig;
	set_last_error(1);
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_putstr_fd("✘ ", STDOUT_FILENO);
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
	exit(1);
}
