/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:06:42 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/26 17:06:11 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_pre_toklist	*make_pre_toklist(t_token token, int *error);

int				add_retokenized_pre_token(t_pre_token pre_token,
					t_toklist **token_list);

static int		add_expanded_token(t_token token, t_toklist **token_list);

int	expand_toklist(t_toklist **token_list)
{
	t_toklist	*watched;
	t_toklist	*expanded_toklist;
	int			error;

	expanded_toklist = NULL;
	watched = *token_list;
	while (watched != NULL)
	{
		error = add_expanded_token(*(watched->data), &expanded_toklist);
		if (error != 0)
			break ;
		watched = watched->next;
	}
	if (error != 0)
		ft_lstclear((t_list **)&expanded_toklist, &free_token);
	else
	{
		ft_lstclear((t_list **)token_list, &free_token);
		*token_list = expanded_toklist;
	}
	return (error);
}

static int	add_expanded_token(t_token token, t_toklist **token_list)
{
	t_pre_toklist	*pre_toklist;
	t_pre_toklist	*watched;
	t_toklist		*retoken_list;
	int				error;

	pre_toklist = make_pre_toklist(token, &error);
	if (error != 0)
		return (error);
	retoken_list = NULL;
	watched = pre_toklist;
	while (watched != NULL)
	{
		error = add_retokenized_pre_token(*(watched->data), &retoken_list);
		if (error != 0)
			break ;
		watched = watched->next;
	}
	ft_lstclear((t_list **)&pre_toklist, &free_token);
	if (error == 0)
		ft_lstadd_back((t_list **)token_list, (t_list *)retoken_list);
	return (error);
}
