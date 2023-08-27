/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:24:15 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/23 18:28:22 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		add_cmd_back(t_token *token, t_ast *tree);
int		add_io_back(t_toklist **token_lst, t_ast *tree);
int		add_separator(t_token *token, t_ast **tree);

t_ast	*make_ast(t_toklist *toklist)
{
	t_ast		*tree;
	t_toklist	*toklist_current;

	tree = (t_ast *)btr_new(NULL);
	if (tree == NULL)
		return (NULL);
	toklist_current = toklist;
	while (toklist_current != NULL)
	{
		if (add_cmd_back(toklist_current->data, tree) == MALLOC_ERROR)
			break ;
		if (add_io_back(&toklist_current, tree) == MALLOC_ERROR)
			break ;
		if (add_separator(toklist_current->data, &tree) == MALLOC_ERROR)
			break ;
		toklist_current = toklist_current->next;
	}
	if (toklist_current == NULL)
		return ((t_ast *)btr_get_root((t_btree *)tree));
	btr_clear(btr_get_root((t_btree *)tree), NULL);
	return (NULL);
}

void	clean_ast(t_ast *ast)
{
	btr_clear(btr_get_root((t_btree *)ast), &free_token);
}
