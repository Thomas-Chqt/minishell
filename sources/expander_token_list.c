/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_token_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:12:27 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/13 13:13:57 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void			free_exp_toklst_node(void *v_node);

t_exp_toklst	*make_exp_toklst(char *str)
{
	t_exp_toklst	*token_lst;
	t_uint64		i;

	token_lst = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		if (exp_add_env(str, &i, &token_lst) == MALLOC_ERROR)
			break ;
		if (exp_add_dquote(str, &i, &token_lst) == MALLOC_ERROR)
			break ;
		if (exp_add_quote(str, &i, &token_lst) == MALLOC_ERROR)
			break ;
		if (exp_add_normal(str, &i, &token_lst) == MALLOC_ERROR)
			break ;
	}
	if (str[i] != '\0')
	{
		ft_lstclear((t_list **)&token_lst, &free_exp_toklst);
		return (NULL);
	}
	return (token_lst);
}

t_exp_toklst	*exp_toklst_new(char *str, t_uint64 len, t_tok_type type)
{
	t_exp_token		*new_token;
	t_exp_toklst	*new_node;

	new_token = malloc(sizeof(t_exp_token));
	if (new_token != NULL)
	{
		new_token->type = type;
		new_token->str = ft_substr(str, 0, len);
		if (new_token->str != NULL)
		{
			new_node = (t_exp_toklst *)ft_lstnew(new_token);
			if (new_node != NULL)
				return (new_node);
			free(new_token->str);
		}
		free(new_token);
	}
	return (NULL);
}

void	free_exp_toklst(t_exp_toklst **lst)
{
	ft_lstclear((t_list **)lst, &free_exp_toklst);
}

static void	free_exp_toklst_node(void *v_node)
{
	t_exp_token	*node;

	node = (t_exp_token *)v_node;
	free(node->str);
	free(node);
}
