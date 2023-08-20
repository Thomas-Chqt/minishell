/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:13:05 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/20 18:43:48 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	add_quote_sub_token_len(const char *cmd, size_t *len);
static int	add_bracket_sub_token_len(const char *cmd, size_t *len);

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
