/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:06:42 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/26 10:41:12 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "environment.h"

int	add_expanded_normal(char *str, t_uint64 *i, t_toklist **list)
{
	size_t		token_len;
	t_toklist	*new_node;

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

int add_expanded_quote(char *str, t_uint64 *i, t_toklist **list)
{
	size_t		token_len;
	t_toklist	*new_node;

	if (str[*i] != '\'')
		return (PARSING_ERROR);
	token_len = ft_strchr(str + (*i) + 1, '\'') - (str + (*i) + 1);
	new_node = toklist_new(QUOTED, ft_substr(str, (*i) + 1, token_len));
	if (new_node == NULL)
		return (MALLOC_ERROR);
	(*i) += 1 + token_len + 1;
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

int add_expanded_dquote(char *str, t_uint64 *i, t_toklist **list)
{
	size_t		token_len;
	t_token		temp_token;
	t_toklist	*new_node;
	int			error;

	if (str[*i] != '\"')
		return (PARSING_ERROR);
	token_len = ft_strchr(str + (*i) + 1, '\"') - (str + (*i) + 1);
	temp_token.data = ft_substr(str, (*i) + 1, token_len);
	if (temp_token.data == NULL)
		return (MALLOC_ERROR);
	temp_token.type = DQUOTED;
	new_node = make_expanded_toklist(temp_token, &error);
	if (error == 0)
	{
		*i += 1 + token_len + 1;
		ft_lstadd_back((t_list **)list, (t_list *)new_node);
	}
	free(temp_token.data);
	return (error);
}

int add_expanded_dollar(char *str, t_uint64 *i, t_toklist **list)
{
	t_toklist	*new_node;

	if (str[*i] != '$')
		return (PARSING_ERROR);
	if (ft_isdigit(str[*i + 1]))
		return (add_substitued_arg(str, i, list));
	if (str[*i + 1] == 123)
		return (add_substitued_brace(str, i, list));
	if (ft_isalpha(str[*i + 1]) || str[*i + 1] == '_')
		return (add_substitued_no_brace(str, i, list));
	new_node = toklist_new(TEXT, ft_strdup("$"));
	if (new_node == NULL)
		return (MALLOC_ERROR);
	(*i) += 1;
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

int add_substitued_arg(char *str, t_uint64 *i, t_toklist **list)
{
	t_toklist	*new_node;

	new_node = toklist_new(TEXT, ft_strdup(""));
	if (new_node == NULL)
		return (MALLOC_ERROR);
	(*i) += 2;
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

int add_substitued_brace(char *str, t_uint64 *i, t_toklist **list)
{
	t_uint64	key_len;
	t_toklist	*new_node;
	int			temp_ret;

	key_len = ft_strchr(str + (*i) + 2, 125) - (str + (*i) + 2);
	if (key_len > 1 || !ft_isdigit(str[*i + 2]))
	{
		temp_ret = add_substitued(str + *i + 2, key_len, list);
		if (temp_ret == BAD_ENVIRONMENT_KEY)
			return (BAD_SUBSTITUTION);
		if (temp_ret != 0)
			return (temp_ret);
		(*i) += 2 + key_len + 1;
		return (0);
	}
	new_node = toklist_new(TEXT, ft_strdup(""));
	if (new_node == NULL)
		return (MALLOC_ERROR);
	(*i) += 4;
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

int add_substitued_no_brace(char *str, t_uint64 *i, t_toklist **list)
{
	size_t	key_len;
	int		temp_ret;

	key_len = valid_key_len(str + *i + 1);
	temp_ret = add_substitued(str + *i + 1, key_len, list);
	if (temp_ret != 0)
		return (temp_ret);
	(*i) += 1 + key_len;
	return (0);
}

int add_substitued(char *str, size_t len, t_toklist **list)
{
	char		*key;
	char		*founded;
	t_toklist	*new_node;
	int			error;

	key = ft_substr(str, 0, len);
	if (key == NULL)
		return (MALLOC_ERROR);
	founded = get_env(key, &error);
	free(key);
	if (error != 0)
		return (error);
	if (founded == NULL)
		founded = ft_strdup("");
	new_node = toklist_new(TEXT, founded);
	if (new_node == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

int add_substitued_last_error(char *str, t_uint64 *i, t_toklist **list)
{
	t_toklist	*new_node;

	if (ft_strncmp(str + *i, "$?", 2) == 0)
	{
		new_node = toklist_new(TEXT, ft_itoa(get_last_error()));
		if (new_node == NULL)
			return (MALLOC_ERROR);
		(*i) += 2;
		ft_lstadd_back((t_list **)list, (t_list *)new_node);
		return (0);
	}
	if (ft_strncmp(str + *i, "${?}", 4) == 0)
	{
		new_node = toklist_new(TEXT, ft_itoa(get_last_error()));
		if (new_node == NULL)
			return (MALLOC_ERROR);
		(*i) += 4;
		ft_lstadd_back((t_list **)list, (t_list *)new_node);
		return (0);
	}
	return (PARSING_ERROR);
}

int	add_substitued_tilde(char *str, t_uint64 *i, t_toklist **list)
{
	char		*founded;
	t_toklist	*new_node;
	int			error;
	
	if (*i == 0 && str[*i] == '~' && (str[(*i) + 1] == '/' || str[(*i) + 1] == '\0'))
	{
		founded = get_env("HOME", &error);
		if (error != 0)
			return (error);
		if (founded == NULL)
			founded = ft_strdup("");
		new_node = toklist_new(TEXT, founded);
		if (new_node == NULL)
			return (MALLOC_ERROR);
		(*i)++;
		ft_lstadd_back((t_list **)list, (t_list *)new_node);
		return (0);
	}
	return (PARSING_ERROR);
}

int add_expanded_next(char *str, t_uint64 *i, t_toklist **list, t_bool dquoted)
{
	int	temp_ret;

	temp_ret = add_substitued_last_error(str, i, list);
	if (temp_ret != PARSING_ERROR)
		return (temp_ret);
	if (!dquoted)
	{
		temp_ret = add_substitued_tilde(str, i, list);
		if (temp_ret != PARSING_ERROR)
			return (temp_ret);
		temp_ret = add_expanded_quote(str, i, list);
		if (temp_ret != PARSING_ERROR)
			return (temp_ret);
		temp_ret = add_expanded_dquote(str, i, list);
		if (temp_ret != PARSING_ERROR)
			return (temp_ret);
	}
	temp_ret = add_expanded_dollar(str, i, list);
	if (temp_ret != PARSING_ERROR)
		return (temp_ret);
	return (add_expanded_normal(str, i, list));
}

t_toklist *make_expanded_toklist(t_token token, int *error)
{
	t_toklist	*token_list;
	t_uint64	i;

	token_list = NULL;
	i = 0;
	while (token.data[i] != 0)
	{
		*error = add_expanded_next(token.data, &i, &token_list, token.type == DQUOTED);
		if (*error != 0)
			break ;
	}
	if (*error != 0)
		ft_lstclear((t_list **)&token_list, &free_token);
	else if (token.type == DQUOTED)
		*error = join_dquoted_toklist(&token_list);
	if (*error != 0)
		ft_lstclear((t_list **)&token_list, &free_token);
	if (*error == BAD_SUBSTITUTION)
		*error = printf_error_msg("minishell: %: bad substitution", &token.data, 1);
	return (token_list);
}

int join_dquoted_toklist(t_toklist **token_list)
{
	t_uint64	str_len;
	char		*str;
	t_toklist	*watched;

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

t_toklist *retoken(t_token token)
{

}

int	add_retoken(t_toklist *retoken, t_toklist **token_list);
{

}