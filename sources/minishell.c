/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 22:20:59 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/26 17:26:46 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

#include "lexer.h"
#include "expander.h"

static const char	*readline_minishell(void);

void	minishell_loop(void)
{
	const char	*cmd;

	while (1)
	{
		cmd = readline_minishell();
		if (cmd == NULL)
			break ;
		if (cmd[0] != '\0')
		{
			add_history(cmd);
		}
		free((void *)cmd);
	}
}

static const char	*readline_minishell(void)
{
	if (get_last_error() == 0)
		ft_putstr_fd("✔︎ ", STDOUT_FILENO);
	else
		ft_putstr_fd("✘ ", STDOUT_FILENO);
	return ((const char *)readline("minishell > "));
}
