/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_pre_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:13:43 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/27 14:04:26 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int			add_pre_token_quote(char *str, t_uint64 *i, t_pre_toklist **list);
int			add_pre_token_dquote(char *str, t_uint64 *i, t_pre_toklist **list);
int			add_pre_token_brace(char *str, t_uint64 *i, t_pre_toklist **list);
int			add_pre_token_no_brace(char *str, t_uint64 *i,
				t_pre_toklist **list);
int			add_pre_token_tilde(char *str, t_uint64 *i, t_pre_toklist **list);

static int	add_pre_token_next(char *str, t_uint64 *i, t_pre_toklist **list,
				t_bool dquoted);
static int	add_pre_token_normal(char *str, t_uint64 *i, t_pre_toklist **list);
static int	add_pre_token_empty(t_pre_toklist **list);
static int	join_dquoted_pre_toklist(t_pre_toklist **token_list);

t_pre_toklist	*make_pre_toklist(t_token token, int *error)
{
	t_pre_toklist	*token_list;
	t_uint64		i;

	token_list = NULL;
	i = 0;
	if (token.data[i] == '\0')
		*error = add_pre_token_empty(&token_list);
	while (token.data[i] != '\0')
	{
		*error = add_pre_token_next(token.data, &i, &token_list,
				token.type == DQUOTED);
		if (*error != 0)
			break ;
	}
	if (*error == 0 && (token.type == QUOTED || token.type == DQUOTED))
		*error = join_dquoted_pre_toklist(&token_list);
	if (*error != 0)
		ft_lstclear((t_list **)&token_list, &free_token);
	if (*error == BAD_SUBSTITUTION)
		*error = printf_error_msg("minishell: %: bad substitution",
				&token.data, 1);
	return (token_list);
}

static int	add_pre_token_next(char *str, t_uint64 *i, t_pre_toklist **list,
				t_bool dquoted)
{
	int			temp_ret;
	int			j;
	static int	(*funcs_dquoted[])(char *, t_uint64 *, t_pre_toklist **) = {
		&add_pre_token_no_brace, &add_pre_token_brace
	};
	static int	(*funcs[])(char *, t_uint64 *, t_pre_toklist **) = {
		&add_pre_token_tilde, &add_pre_token_quote, &add_pre_token_dquote,
		&add_pre_token_no_brace, &add_pre_token_brace
	};

	j = 0;
	while (j < 2 + ((dquoted == false) * 3))
	{
		if (dquoted)
			temp_ret = funcs_dquoted[j](str, i, list);
		else
			temp_ret = funcs[j](str, i, list);
		if (temp_ret != PARSING_ERROR)
			return (temp_ret);
		j++;
	}
	return (add_pre_token_normal(str, i, list));
}

static int	add_pre_token_normal(char *str, t_uint64 *i, t_pre_toklist **list)
{
	size_t			token_len;
	t_pre_toklist	*new_node;

	token_len = 1;
	while ((str + *i)[token_len] != '\0'
			&& (str + *i)[token_len] != '\''
			&& (str + *i)[token_len] != '\"'
			&& (str + *i)[token_len] != '$')
		token_len++;
	new_node = toklist_new(TEXT, ft_substr(str, (*i), token_len));
	if (new_node == NULL)
		return (MALLOC_ERROR);
	(*i) += token_len;
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

static int	add_pre_token_empty(t_pre_toklist **list)
{
	t_pre_toklist	*new_node;

	new_node = toklist_new(TEXT, ft_strdup(""));
	if (new_node == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

static int	join_dquoted_pre_toklist(t_pre_toklist **token_list)
{
	t_uint64		str_len;
	char			*str;
	t_pre_toklist	*watched;

	str_len = 0;
	watched = *token_list;
	while (watched != NULL)
	{
		str_len += ft_strlen(watched->data->data);
		watched = watched->next;
	}
	str = ft_calloc(str_len + 1, sizeof(char));
	if (str == NULL)
		return (MALLOC_ERROR);
	watched = *token_list;
	while (watched != NULL)
	{
		ft_strlcat(str, watched->data->data, str_len + 1);
		watched = watched->next;
	}
	ft_lstclear((t_list **)&((*token_list)->next), &free_token);
	free((*token_list)->data->data);
	(*token_list)->data->data = str;
	(*token_list)->data->type = DQUOTED;
	return (0);
}
