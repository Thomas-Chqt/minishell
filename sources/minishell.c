/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 22:20:59 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/23 18:49:18 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "environment.h"

void	minishell_loop(void)
{
	const char	*cmd;
	t_ast		*ast;

	while (1)
	{
		if (get_last_error() == 0)
			ft_putstr_fd("✔︎ ", STDOUT_FILENO);
		else
			ft_putstr_fd("✘ ", STDOUT_FILENO);
		cmd = (const char *)readline("minishell > ");
		if (cmd == NULL)
			break ;
		if (cmd[0] != '\0')
		{
			add_history(cmd);
			ast = parse_cmd(cmd);
			if (ast != NULL)
			{
				set_last_error(execute_ast(ast));
				clean_ast(ast);
			}
		}
		free((void *)cmd);
	}
}

t_ast	*parse_cmd(const char *cmd)
{
	t_ast		*ast;
	t_toklist	*token_list;

	token_list = make_toklist(cmd);
	if (token_list != NULL)
	{
		ast = make_ast(token_list);
		if (ast != NULL)
		{
			ft_lstclear((t_list **)&token_list, NULL);
			return (ast);
		}
		else
		{
			set_last_error(print_error(MALLOC_ERROR));
			ft_lstclear((t_list **)token_list, &free_token);
		}
	}
	return (NULL);
}
