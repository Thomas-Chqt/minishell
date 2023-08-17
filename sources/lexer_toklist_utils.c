/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_toklist_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:54:13 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/17 14:54:47 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_toklist	*toklist_new(t_token_type type, char *data)
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

void	free_token(void *token)
{
	if (token == NULL)
		return ;
	free(((t_token *)token)->data);
	free(token);
}
