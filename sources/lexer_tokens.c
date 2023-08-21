/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:31:29 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/21 12:22:14 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_toklist	*toklist_new(t_token_type type, char *data);

int			set_text_token_len(const char *cmd, size_t *len);

int	toklist_text_new(const char *cmd, t_uint64 *i, t_toklist **list)
{
	size_t		token_len;
	t_toklist	*new_node;
	int			temp_ret;

	temp_ret = set_text_token_len(cmd + (*i), &token_len);
	if (temp_ret != 0)
		return (temp_ret);
	new_node = toklist_new(TEXT, ft_substr(cmd, (*i), token_len));
	if (new_node == NULL)
		return (MALLOC_ERROR);
	(*i) += token_len;
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
