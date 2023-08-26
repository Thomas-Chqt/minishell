/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:12:11 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/26 17:28:39 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "environment.h"

int			recurse_full_cmd(const char *cmd, t_uint64 *i, t_toklist **list);

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

t_toklist	*make_toklist(const char *cmd)
{
	t_toklist	*new_lst;
	t_uint64	i;
	int			error_code;

	i = 0;
	new_lst = NULL;
	error_code = recurse_full_cmd(cmd, &i, &new_lst);
	if (error_code == 0)
		return (new_lst);
	set_last_error(print_error(error_code));
	return (NULL);
}

void	free_token(void *token)
{
	if (token == NULL)
		return ;
	free(((t_token *)token)->data);
	free(token);
}
