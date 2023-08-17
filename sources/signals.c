/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:30:06 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/17 16:07:33 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

int	sig_interactive_mode(void)
{
	struct sigaction	sig_int_sa;
	struct sigaction	sig_quit_sa;

	sig_int_sa.sa_handler = &sigint_handler_new_line;
	sig_int_sa.sa_flags = SA_RESTART;
	sig_quit_sa.sa_handler = SIG_IGN;
	sig_quit_sa.sa_flags = 0;
	if (sigaction(SIGINT, &sig_int_sa, NULL) != 0)
		return (SIGACTION_ERROR);
	if (sigaction(SIGQUIT, &sig_quit_sa, NULL) != 0)
		return (SIGACTION_ERROR);
	return (0);
}

int	sig_forwarding_mode(void)
{
	struct sigaction	sig_int_sa;
	struct sigaction	sig_quit_sa;

	sig_int_sa.sa_handler = &sig_forwarding;
	sig_int_sa.sa_flags = SA_RESTART;
	sig_quit_sa.sa_handler = &sig_forwarding;
	sig_quit_sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sig_int_sa, NULL) != 0)
		return (SIGACTION_ERROR);
	if (sigaction(SIGQUIT, &sig_quit_sa, NULL) != 0)
		return (SIGACTION_ERROR);
	return (0);
}

int	sig_heredoc_mode(void)
{
	struct sigaction	sig_int_sa;

	sig_int_sa.sa_handler = &sigint_handler_exit;
	sig_int_sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sig_int_sa, NULL) != 0)
		return (SIGACTION_ERROR);
	return (0);
}
