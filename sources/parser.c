/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:24:15 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/12 22:24:08 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*make_ast(t_toklist *toklist)
{
	t_ast		*tree;
	t_toklist	*toklist_current;

	tree = (t_ast *)btr_new(NULL);
	if (tree == NULL)
	{
		print_error(MALLOC_ERROR);
		return (NULL);
	}
	toklist_current = toklist;
	while (toklist_current != NULL)
	{
		if (add_cmd_back(toklist_current->data, tree) == MALLOC_ERROR)
			break ;
		if (add_io(&toklist_current, tree) == MALLOC_ERROR)
			break ;
		if (add_separator(toklist_current->data, &tree) == MALLOC_ERROR)
			break ;
		toklist_current = toklist_current->next;
	}
	if (toklist_current == NULL)
		return ((t_ast *)btr_get_root((t_btree *)tree));
	btr_clear(btr_get_root((t_btree *)tree), NULL);
	print_error(MALLOC_ERROR);
	return (NULL);
}

void	clean_ast(t_ast *ast)
{
	btr_clear(btr_get_root((t_btree *)ast), &free_token);
}

t_bool	is_io_token(t_token *token)
{
	return (
		token->type == DLESS
		|| token->type == DGREAT
		|| token->type == LESS
		|| token->type == GREAT
	);
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
			if (expand_ast(ast) == 0)
				return (ast);
			clean_ast(ast);
		}
		else
			clean_toklist(&token_list);
	}
	return (NULL);
}
