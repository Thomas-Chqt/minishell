/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_add_to_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:33:02 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/19 18:37:10 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	exp_lstadd_quote(char *str, t_uint64 *i, t_str_list **list)
{
	
}

int	exp_lstadd_dquote(char *str, t_uint64 *i, t_str_list **list)
{

}

int	exp_lstadd_bracket(char *str, t_uint64 *i, t_str_list **list)
{
	size_t	token_len;
	int		temp_ret;

	if (str[*i] != '$' || str[(*i) + 1] != 123)
		return (PARSING_ERROR);
	token_len = 0;
	while ((str + (*i) + 2)[token_len] != 0 && (str + (*i) + 2)[token_len] != 125)
		token_len++;
	temp_ret = add_substitued(str + (*i) + 2, token_len, list);
	if (temp_ret != 0)
		return (temp_ret);
	*i += 2 + token_len + 1;
	return (0);
}

int	exp_lstadd_no_bracket(char *str, t_uint64 *i, t_str_list **list)
{
	if (str[*i] != '$' || !ft_isalpha(str[(*i) + 1]) || str[(*i) + 1] != '_')
		return (PARSING_ERROR);
}

int	exp_lstadd_normal(char *str, t_uint64 *i, t_str_list **list)
{
	size_t		token_len;
	t_str_list	*new_node;

	token_len = 1;
	while (is_end_nomal_token((str + (*i))[token_len]) == false)
		token_len++;
	new_node = (t_str_list *)ft_lstnew(NULL);
	if (new_node != NULL)
	{
		new_node->str = ft_substr(str, (unsigned int)*i, token_len);
		if (new_node->str != NULL)
		{
			ft_lstadd_back((t_list **)list, (t_list *)new_node);
			*i += token_len;
			return (0);
		}
		free(new_node);
	}
	return (MALLOC_ERROR);
}
