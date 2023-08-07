/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 22:20:59 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/07 12:56:34 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(void)
{
	const char	*cmd;
	t_ast		*ast;

	while (1)
	{
		cmd = (const char *)readline("minishell > ");
		if (cmd == NULL)
			continue ;
		if (cmd[0] != '\0')
		{
			add_history(cmd);
			ast = parse_cmd(cmd);
			if (ast != NULL)
			{
				execute_ast(ast);
				clean_ast(ast);
			}
		}
		free((void *)cmd);
	}
}
