/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 22:19:03 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/12 20:15:54 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_cmd_back(t_token *token, t_ast *tree)
{
	t_btree	*new_node;

	if (token->type != TEXT)
		return (PARSING_ERROR);
	if (tree->data == NULL)
		tree->data = token;
	else
	{
		new_node = btr_new((void *)token);
		if (new_node == NULL)
			return (MALLOC_ERROR);
		btr_set_r_child(btr_get_last((t_btree *)tree, preorder), new_node);
	}
	return (0);
}

int	add_io(t_toklist **token_lst, t_ast *tree)
{
	if (is_io_token((*token_lst)->data) == false)
		return (PARSING_ERROR);
	if ((*token_lst)->data->type == DLESS)
		return (add_io_front(token_lst, tree));
	return (add_io_back(token_lst, tree));
}

int	add_io_back(t_toklist **token_lst, t_ast *tree)
{
	t_btree	*new_node;
	t_btree	*new_node2;

	new_node = btr_new((void *)(*token_lst)->data);
	*token_lst = (*token_lst)->next;
	if (new_node != NULL)
	{
		new_node2 = btr_new((void *)(*token_lst)->data);
		if (new_node2 != NULL)
		{
			btr_set_l_child(new_node, new_node2);
			if (tree->left == NULL)
				btr_set_l_child((t_btree *)tree, new_node);
			else
				btr_set_r_child(btr_get_last((t_btree *)tree->left, preorder),
					new_node);
			return (0);
		}
		free(new_node);
	}
	return (MALLOC_ERROR);
}

int	add_io_front(t_toklist **token_lst, t_ast *tree)
{
	t_btree	*new_node;
	t_btree	*new_node2;

	new_node = btr_new((void *)(*token_lst)->data);
	*token_lst = (*token_lst)->next;
	if (new_node != NULL)
	{
		new_node2 = btr_new((void *)(*token_lst)->data);
		if (new_node2 != NULL)
		{
			btr_set_l_child(new_node, new_node2);
			if (tree->left == NULL)
				btr_set_l_child((t_btree *)tree, new_node);
			else
			{
				btr_set_r_child(new_node, (t_btree *)tree->left);
				btr_set_l_child((t_btree *)tree, new_node);
			}
			return (0);
		}
		free(new_node);
	}
	return (MALLOC_ERROR);
}

int	add_separator(t_token *token, t_ast **tree)
{
	t_btree	*new_node;

	if (token->type == TEXT || is_io_token(token) == true)
		return (PARSING_ERROR);
	new_node = btr_new((void *)token);
	if (new_node == NULL)
		return (MALLOC_ERROR);
	btr_set_l_child(new_node, btr_get_root(*((t_btree **)tree)));
	*tree = (t_ast *)new_node;
	new_node = btr_new(NULL);
	if (new_node == NULL)
		return (MALLOC_ERROR);
	btr_set_r_child(*((t_btree **)tree), new_node);
	*tree = (*tree)->right;
	return (0);
}
