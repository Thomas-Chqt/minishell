/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_add_pre_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:16:02 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/26 17:07:30 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "environment.h"

int				add_pre_token_subst(char *str, t_uint64 i, size_t len,
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
	if (error == 0)
	{
		*i += 1 + token_len + 1;
		ft_lstadd_back((t_list **)list, (t_list *)new_nodes);
	}
	free(subed_str);
	return (error);
}

int	add_pre_token_brace(char *str, t_uint64 *i, t_pre_toklist **list)
{
	size_t	key_len;
	size_t	added_len;
	char	*close_brace;
	int		error;

	if (str[*i] != '$' || str[*i + 1] != 123)
		return (PARSING_ERROR);
	added_len = 3;
	close_brace = ft_strchr(str + *i + 2, 125);
	if (close_brace == NULL)
		return (PARSING_ERROR);
	key_len = close_brace - (str + *i + 2);
	added_len += key_len;
	error = add_pre_token_subst(str, *i + 2, key_len, list);
	if (error == 0)
		*i += added_len;
	return (error);
}

int	add_pre_token_no_brace(char *str, t_uint64 *i, t_pre_toklist **list)
{
	size_t	key_len;
	size_t	added_len;
	char	*close_brace;
	int		error;

	if (str[*i] != '$' || (!ft_isalnum(str[*i + 1]) && str[*i + 1] != '_'))
		return (PARSING_ERROR);
	added_len = 1;
	key_len = 1;
	key_len += valid_key_len(str + *i + 2);
	added_len += key_len;
	error = add_pre_token_subst(str, *i + 1, key_len, list);
	if (error == 0)
		*i += added_len;
	return (error);
}

int	add_pre_token_tilde(char *str, t_uint64 *i, t_pre_toklist **list)
{
	if (i != 0 || str[*i] != '~' || (str[*i + 1] != '\0' && str[*i + 1] != '/'))
		return (PARSING_ERROR);
	return (add_pre_token_subst(str, *i + 1, 1, list));
}
