/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:31:29 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/12 19:48:05 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_toklist	*toklist_new(t_token_type type, char *data);

int	toklist_text_new(const char *cmd, t_uint64 *i, t_toklist **list)
{
	t_uint64	token_start;
	char		quote;
	t_toklist	*new_node;

	token_start = (*i);
	while (cmd[*i] != '\0' && ft_strchr("<>| \t\n\v\f\r", cmd[*i]) == NULL)
	{
		if (cmd[*i] == '\"' || cmd[*i] == '\'')
		{
			quote = cmd[(*i)++];
			while (cmd[*i] != quote && cmd[*i] != '\0')
				(*i)++;
		}
		if (cmd[*i] == '\0')
			return (MISSING_QUOTE + quote);
		(*i)++;
	}
	if (token_start == *i)
		return (PARSING_ERROR);
	new_node = toklist_new(TEXT, ft_substr(cmd, token_start,
				(*i) - token_start));
	if (new_node == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

int	toklist_pipe_new(const char *cmd, t_uint64 *i, t_toklist **list)
{
	t_toklist	*new_node;

	if (ft_strncmp(cmd + (*i), "|", 1) == 0)
	{
		new_node = toklist_new(PIPE, NULL);
		if (new_node == NULL)
			return (MALLOC_ERROR);
		(*i)++;
		ft_lstadd_back((t_list **)list, (t_list *)new_node);
		return (0);
	}
	return (PARSING_ERROR);
}

int	toklist_io_new(const char *cmd, t_uint64 *i, t_toklist **list)
{
	t_toklist	*new_node;

	if (cmd[*i] != '<' && cmd[*i] != '>')
		return (PARSING_ERROR);
	new_node = toklist_new(DLESS, NULL);
	if (new_node == NULL)
		return (MALLOC_ERROR);
	if (cmd[*i] == '<' && cmd[*i + 1] == '<')
		new_node->data->type = DLESS;
	else if (cmd[*i] == '<')
		new_node->data->type = LESS;
	if (cmd[*i] == '>' && cmd[*i + 1] == '>')
		new_node->data->type = DGREAT;
	else if (cmd[*i] == '>')
		new_node->data->type = GREAT;
	if (new_node->data->type == DGREAT || new_node->data->type == DLESS)
		(*i) += 2;
	else
		(*i)++;
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

void	free_token(void *token)
{
	free(((t_token *)token)->data);
	free(token);
}

static t_toklist	*toklist_new(t_token_type type, char *data)
{
	t_token		*new_token;
	t_toklist	*new_node;

	if (type == TEXT && data == NULL)
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
