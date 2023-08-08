/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 22:20:59 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/08 13:43:48 by tchoquet         ###   ########.fr       */
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
			if (str_cmp(cmd, "exit") == 0)
			{
				free((void *)cmd);
				break ;
			}
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
