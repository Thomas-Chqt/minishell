/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_add_token_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:19:27 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/24 16:22:50 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	add_quote_sub_token_len(const char *cmd, size_t *len);
static int	add_bracket_sub_token_len(const char *cmd, size_t *len);

t_toklist	*toklist_new(t_token_type type, char *data)
{
	t_token		*new_token;
	t_toklist	*new_node;

	if (type >= TEXT && data == NULL)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (new_token != NULL)
	{
		new_token->type = type;
		new_token->data = data;
		new_node = (t_toklist *)ft_lstnew((void *)new_token);
		if (new_node != NULL)
			return (new_node);
		free(new_token);
	}
	free(data);
	return (NULL);
}

int	set_text_token_len(const char *cmd, size_t *len)
{
	int	temp_ret;

	*len = 0;
	while (cmd[*len] != '\0' && ft_strchr("<>| \t\n\v\f\r", cmd[*len]) == NULL)
	{
		temp_ret = add_quote_sub_token_len(cmd, len);
		if (temp_ret != 0)
			return (temp_ret);
		temp_ret = add_bracket_sub_token_len(cmd, len);
		if (temp_ret != 0)
			return (temp_ret);
		(*len)++;
	}
	if (*len == 0)
		return (PARSING_ERROR);
	return (0);
}

static int	add_quote_sub_token_len(const char *cmd, size_t *len)
{
	int	temp_ret;

	if (cmd[*len] == '\'')
	{
		while (cmd[++(*len)] != '\'' && cmd[*len] != '\0')
			;
		if (cmd[*len] == '\0')
			return (MISSING_SQUOTE);
	}
	else if (cmd[*len] == '\"')
	{
		while (cmd[++(*len)] != '\"' && cmd[*len] != '\0')
		{
			temp_ret = add_bracket_sub_token_len(cmd, len);
			if (temp_ret != 0)
				return (temp_ret);
		}
		if (cmd[*len] == '\0')
			return (MISSING_DQUOTE);
	}
	return (0);
}

static int	add_bracket_sub_token_len(const char *cmd, size_t *len)
{
	if (ft_strncmp(cmd + (*len), "${", 2) == 0)
	{
		while (cmd[*len] != '}' && cmd[*len] != '\0')
			(*len)++;
		if (cmd[*len] == '\0')
			return (MISSING_CLOSE_BRACKET);
	}
	return (0);
}
