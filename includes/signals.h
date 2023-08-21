/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:27:33 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/21 11:25:55 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"
# include "error.h"

int		sig_interactive_mode(void);
int		sig_forwarding_mode(void);
int		sig_heredoc_mode(void);
int		sig_heredoc_parent_mode(void);

#endif // SIGNALS_H