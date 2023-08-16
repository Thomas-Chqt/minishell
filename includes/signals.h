/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:27:33 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/16 23:11:56 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "error.h"

int		sig_interactive_mode(void);
int		sig_forwarding_mode(void);
int		sig_heredoc_mode(void);

void	sigint_handler_new_line(int sig);
void	sig_forwarding(int sig);
void	sigint_handler_exit(int sig);

#endif // SIGNALS_H