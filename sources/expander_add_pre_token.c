/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_add_pre_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:16:02 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/27 13:15:24 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "environment.h"

int				add_pre_token_subst(char *str, size_t len,
					t_pre_toklist **list);

t_pre_toklist	*make_pre_toklist(t_token token, int *error);

int	add_pre_token_quote(char *str, t_uint64 *i, t_pre_toklist **list)
{
	char			*close_quote;
	size_t			token_len;
	t_pre_toklist	*new_node;

	if (str[*i] != '\'')
		return (PARSING_ERROR);
	close_quote = ft_strchr(str + (*i) + 1, '\'');
	if (close_quote == NULL)
		return (PARSING_ERROR);
	token_len = close_quote - (str + (*i) + 1);
	new_node = toklist_new(QUOTED, ft_substr(str, (*i) + 1, token_len));
	if (new_node == NULL)
		return (MALLOC_ERROR);
	(*i) += 1 + token_len + 1;
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

int	add_pre_token_dquote(char *str, t_uint64 *i, t_pre_toklist **list)
{
	size_t			token_len;
	char			*subed_str;
	t_pre_toklist	*new_nodes;
	int				error;
	t_token			tmp_token;

	if (str[*i] != '\"' || ft_strchr(str + (*i) + 1, '\"') == NULL)
		return (PARSING_ERROR);
	token_len = ft_strchr(str + (*i) + 1, '\"') - (str + (*i) + 1);
	subed_str = ft_substr(str, (*i) + 1, token_len);
	if (subed_str == NULL)
		return (MALLOC_ERROR);
	tmp_token.data = subed_str;
	tmp_token.type = DQUOTED;
	new_nodes = make_pre_toklist(tmp_token, &error);
	free(subed_str);
	if (error == 0)
	{
		*i += 1 + token_len + 1;
		ft_lstadd_back((t_list **)list, (t_list *)new_nodes);
	}
	else
		ft_lstclear((t_list **)&new_nodes, &free_token);
	return (error);
}

int	add_pre_token_brace(char *str, t_uint64 *i, t_pre_toklist **list)
{
	size_t	key_len;
	char	*close_brace;
	int		error;

	if (str[*i] != '$' || str[*i + 1] != 123)
		return (PARSING_ERROR);
	close_brace = ft_strchr(str + *i + 2, 125);
	if (close_brace == NULL)
		return (PARSING_ERROR);
	key_len = close_brace - (str + *i + 2);
	error = add_pre_token_subst(str + *i + 2, key_len, list);
	if (error == 0)
		*i += key_len + 3;
	return (error);
}

int	add_pre_token_no_brace(char *str, t_uint64 *i, t_pre_toklist **list)
{
	size_t	key_len;
	int		error;

	if (str[*i] != '$')
		return (PARSING_ERROR);
	key_len = valid_key_len(str + *i + 1);
	if (key_len == 0)
		return (PARSING_ERROR);
	error = add_pre_token_subst(str + *i + 1, key_len, list);
	if (error == 0)
		*i += key_len + 1;
	return (error);
}

int	add_pre_token_special(char *str, t_uint64 *i, t_pre_toklist **list)
{
	int	error;

	if (str[*i] != '$' || (!ft_isdigit(str[*i + 1]) && str[*i + 1] != '?'))
		return (PARSING_ERROR);
	error = add_pre_token_subst(str + *i + 1, 1, list);
	if (error == 0)
		*i += 2;
	return (error);
}
