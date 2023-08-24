/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:06:05 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/25 17:03:54 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "environment.h"

static t_bool	should_break(int error, int *returned);

t_toklist	*make_toklist(const char *cmd)
{
	t_toklist	*token_list;
	t_uint64	i;
	int			error;

	i = 0;
	token_list = NULL;
	while (cmd[i] != '\0')
	{
		while (is_whitespace(cmd[i]))
			i++;
		if (should_break(add_text_token(cmd, &i, &token_list), &error))
			break ;
		if (should_break(add_pipe_token(cmd, &i, &token_list), &error))
			break ;
		if (should_break(add_io_token(cmd, &i, &token_list), &error))
			break ;
	}
	if (cmd[i] != '\0')
	{
		set_last_error(print_error(error));
		ft_lstclear((t_list **)&token_list, &free_token);
	}
	return (token_list);
}

void	free_token(void *token)
{
	if (token == NULL)
		return ;
	free(((t_token *)token)->data);
	free(token);
}

static t_bool	should_break(int error, int *returned)
{
	*returned = error;

	if (error == MALLOC_ERROR)
		return (true);
	if (error == MISSING_SQUOTE)
		return (true);
	if (error == MISSING_DQUOTE)
		return (true);
	if (error == MISSING_CLOSE_BRACKET)
		return (true);
	return (false);
}