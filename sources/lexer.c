/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:02:15 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/29 16:14:55 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define STATE_NORMAL 1
#define STATE_QUOTE 2
#define STATE_DQUOTE 3

static t_toklist	*toklist_new(t_token_type type, char *data);
static int			add_token(char *command, t_uint64 *i, t_toklist **lst_head);
static int			add_text_token(char *command, t_uint64 *i, t_toklist **lst_head);
static int			lstadd_back_wrapper(t_toklist **lst, t_toklist *new);
static void			free_token(void *token);

t_toklist	*make_toklist(char *command)
{
	t_toklist	*toklist;
	t_uint64	i;

	toklist = NULL;
	i = -1;
	while (command[++i] != '\0')
	{
		if (add_token(command, &i, &toklist) == 0)
			continue ;
		if (add_text_token(command, &i, &toklist) != 0)
		{
			ft_lstclear((t_list **)&toklist, &free_token);
			return (NULL);
		}
	}
	return (toklist);
}

static int	add_token(char *command, t_uint64 *i, t_toklist **lst_head)
{
	(*i) += 2;
	if (ft_strncmp(command + (*i - 2), "<<", 2) == 0)
		return (lstadd_back_wrapper(lst_head, toklist_new(DLESS, NULL)));
	if (ft_strncmp(command + (*i - 2), ">>", 2) == 0)
		return (lstadd_back_wrapper(lst_head, toklist_new(DGREAT, NULL)));
	(*i)--;
	if (ft_strncmp(command + (*i - 1), "<", 1) == 0)
		return (lstadd_back_wrapper(lst_head, toklist_new(LESS, NULL)));
	if (ft_strncmp(command + (*i - 1), ">", 1) == 0)
		return (lstadd_back_wrapper(lst_head, toklist_new(GREAT, NULL)));
	if (ft_strncmp(command + (*i - 1), "|", 1) == 0)
		return (lstadd_back_wrapper(lst_head, toklist_new(PIPE, NULL)));
	(*i)--;
	return (1);
}

static int	add_text_token(char *command, t_uint64 *i, t_toklist **lst_head)
{
	int			state;
	t_uint64	token_start;

	while (is_whitespace(command[*i]))
		(*i)++;
	state = STATE_NORMAL;
	token_start = (*i);
	while (command[*i] != '\0' && ((state != STATE_NORMAL) || (state == STATE_NORMAL && !(command[*i] == '<' || command[*i] == '>' || command[*i] == '|' || is_whitespace(command[*i])))))
	{
		if (state == STATE_NORMAL)
		{
			if (command[*i] == '\'')
				state = STATE_QUOTE;
			if (command[*i] == '\"')
				state = STATE_DQUOTE;
		}
		else if (state == STATE_QUOTE && command[*i] == '\'')
			state = STATE_NORMAL;
		else if (state == STATE_DQUOTE && command[*i] == '\"')
			state = STATE_NORMAL;
		(*i)++;
	}
	if (state != STATE_NORMAL)
		return (1);
	return (lstadd_back_wrapper(lst_head, toklist_new(TEXT, ft_substr(command, token_start, (*i) - token_start))));
}

static int	lstadd_back_wrapper(t_toklist **lst, t_toklist *new)
{
	ft_lstadd_back((t_list **)lst, (t_list *)new);
	return (0);
}

static t_toklist	*toklist_new(t_token_type type, char *data)
{
	t_token		*new_token;
	t_toklist	*new_node;

	new_token = malloc(sizeof(t_token));
	new_token->type = type;
	new_token->type = data;
	if (new_token != NULL)
	{
		new_node = (t_toklist *)ft_lstnew((void *)new_token);
		if (new_node != NULL)
			return (new_node);
		free(new_token);
	}
	return (NULL);
}

static void	free_token(void *token)
{
	free(((t_token *)token)->data);
	free(token);
}
