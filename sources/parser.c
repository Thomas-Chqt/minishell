/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:24:15 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/03 14:35:23 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MALLOC_ERROR 1111

static int		add_cmd_back(t_token *token, t_ast *tree);
static int		add_io(t_toklist **token_lst, t_ast *tree);
static int		add_io_back(t_toklist **token_lst, t_ast *tree);
static int		add_io_front(t_toklist **token_lst, t_ast *tree);
static int		add_separator(t_token *token, t_ast **tree);
static t_bool	is_io_token(t_token *token);

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
		if (add_io(&toklist_current, tree) == MALLOC_ERROR)
			break ;
		if (add_separator(toklist_current->data, &tree) == MALLOC_ERROR)
			break ;
		toklist_current = toklist_current->next;
	}
	if (toklist_current != NULL)
	{
		btr_clear(btr_get_root((t_btree *)tree), NULL);
		return (NULL);
	}
	return ((t_ast *)btr_get_root((t_btree *)tree));
}

static int	add_cmd_back(t_token *token, t_ast *tree)
{
	t_btree	*new_node;

	if (token->type != TEXT)
		return (1);
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

static int	add_io(t_toklist **token_lst, t_ast *tree)
{
	if (is_io_token((*token_lst)->data) == false)
		return (1);
	if ((*token_lst)->data->type == DLESS)
		return (add_io_front(token_lst, tree));
	if ((*token_lst)->data->type == DGREAT)
		return (add_io_front(token_lst, tree));
	return (add_io_back(token_lst, tree));
}

static int	add_io_back(t_toklist **token_lst, t_ast *tree)
{
	t_btree	*new_node;
	t_btree	*new_node2;

	if (is_io_token((*token_lst)->data) == false)
		return (1);
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

static int	add_io_front(t_toklist **token_lst, t_ast *tree)
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

static int	add_separator(t_token *token, t_ast **tree)
{
	t_btree	*new_node;

	if (token->type == TEXT || is_io_token(token) == true)
		return (1);
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

static t_bool	is_io_token(t_token *token)
{
	return (
		token->type == DLESS
		|| token->type == DGREAT
		|| token->type == LESS
		|| token->type == GREAT
	);
}
