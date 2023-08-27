/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_retokenize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:59:57 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/26 17:01:20 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static t_toklist	*retokenize_pre_token(t_pre_token token);
static t_toklist	*retokenize_pre_token_split(t_token token);

int	add_retokenized_pre_token(t_pre_token pre_token, t_toklist **token_list)
{
	t_toklist	*rtok_lst;
	t_toklist	*last_node;
	char		*joined_strs;

	rtok_lst = retokenize_pre_token(pre_token);
	if (rtok_lst == NULL)
		return (MALLOC_ERROR);
	if (*token_list == NULL)
		ft_lstadd_back((t_list **)token_list, (t_list *)rtok_lst);
	else
	{
		last_node = (t_toklist *)lst_rmvlast((t_list **)token_list);
		joined_strs = ft_strjoin(last_node->data->data, rtok_lst->data->data);
		if (joined_strs == NULL)
		{
			ft_lstclear((t_list **)&rtok_lst, &free_token);
			ft_lstadd_back((t_list **)token_list, (t_list *)last_node);
			return (MALLOC_ERROR);
		}
		free(rtok_lst->data->data);
		rtok_lst->data->data = joined_strs;
		ft_lstadd_back((t_list **)token_list, (t_list *)rtok_lst);
		ft_lstclear((t_list **)&last_node, &free_token);
	}
	return (0);
}

static t_toklist	*retokenize_pre_token(t_pre_token token)
{
	t_toklist	*token_list;

	if (token.type == QUOTED || token.type == DQUOTED)
		token_list = toklist_new(TEXT, ft_strdup(token.data));
	else
		token_list = retokenize_pre_token_split(token);
	return (token_list);
}

static t_toklist	*retokenize_pre_token_split(t_token token)
{
	t_toklist	*token_list;
	t_toklist	*new_node;
	char		**splited_str;
	t_uint64	i;

	splited_str = str_split_whitespc(token.data);
	if (splited_str == NULL)
		return (NULL);
	token_list = NULL;
	i = 0;
	while (splited_str[i] != NULL)
	{
		new_node = toklist_new(TEXT, ft_strdup(splited_str[i]));
		if (new_node == NULL)
			break ;
		ft_lstadd_back((t_list **)&token_list, (t_list *)new_node);
		i++;
	}
	if (splited_str[i] != NULL)
		ft_lstclear((t_list **)&token_list, &free_token);
	free_splited_str(splited_str);
	return (token_list);
}
