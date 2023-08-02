/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:02:15 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/30 18:28:27 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NORMAL 1
#define QUOTE 2
#define DQUOTE 3

static int	add_text(char *command, t_uint64 *i, t_toklist **lst_head);
static int	add_token(char *command, t_uint64 *i, t_toklist **lst_head);
static int	add_token_2(char *command, t_uint64 *i, t_toklist **lst_head);
static int	add_token_3(char *command, t_uint64 *i, t_toklist **lst_head);

int	fill_toklist(char *command, t_toklist **toklist_head)
{
	t_uint64	i;
	int			temp_ret;

	i = 0;
	while (command[i] != '\0')
	{
		while (is_whitespace(command[i]))
			i++;
		if (command[i] == '\0')
			return (0);
		temp_ret = add_token(command, &i, toklist_head);
		if (temp_ret == 0)
			continue ;
		if (temp_ret == 2)
			return (2);
		temp_ret = add_text(command, &i, toklist_head);
		if (temp_ret == 0)
			continue ;
		if (temp_ret == 2)
			return (2);
		return (1);
	}
	return (0);
}

static int	add_text(char *command, t_uint64 *i, t_toklist **lst_head)
{
	t_uint64	token_start;
	char		temp;
	t_toklist	*new_node;

	token_start = (*i);
	while (command[*i] != '\0' && ft_strchr("<>| \t\n\v\f\r", command[*i]) == NULL)
	{
		if (command[*i] == '\"' || command[*i] == '\'')
		{
			temp = command[(*i)++];
			while (command[*i] != temp && command[*i] != '\0')
				(*i)++;
		}
		if (command[*i] == '\0')
			return (1);
		(*i)++;
	}
	new_node = toklist_new(TEXT, ft_substr(command, token_start,
				(*i) - token_start));
	if (new_node == NULL)
		return (2);
	ft_lstadd_back((t_list **)lst_head, (t_list *)new_node);
	return (0);
}

static int	add_token(char *command, t_uint64 *i, t_toklist **lst_head)
{
	t_toklist	*new_node;

	if (ft_strncmp(command + (*i), "<<", 2) == 0)
	{
		new_node = toklist_new(DLESS, NULL);
		if (new_node == NULL)
			return (2);
		(*i) += 2;
		ft_lstadd_back((t_list **)lst_head, (t_list *)new_node);
		return (0);
	}
	if (ft_strncmp(command + (*i), ">>", 2) == 0)
	{
		new_node = toklist_new(DGREAT, NULL);
		if (new_node == NULL)
			return (2);
		(*i) += 2;
		ft_lstadd_back((t_list **)lst_head, (t_list *)new_node);
		return (0);
	}
	return (add_token_2(command, i, lst_head));
}

static int	add_token_2(char *command, t_uint64 *i, t_toklist **lst_head)
{
	t_toklist	*new_node;

	if (ft_strncmp(command + (*i), "<", 1) == 0)
	{
		new_node = toklist_new(LESS, NULL);
		if (new_node == NULL)
			return (2);
		(*i) += 1;
		ft_lstadd_back((t_list **)lst_head, (t_list *)new_node);
		return (0);
	}
	if (ft_strncmp(command + (*i), ">", 1) == 0)
	{
		new_node = toklist_new(GREAT, NULL);
		if (new_node == NULL)
			return (2);
		(*i) += 1;
		ft_lstadd_back((t_list **)lst_head, (t_list *)new_node);
		return (0);
	}
	return (add_token_3(command, i, lst_head));
}

static int	add_token_3(char *command, t_uint64 *i, t_toklist **lst_head)
{
	t_toklist	*new_node;

	if (ft_strncmp(command + (*i), "|", 1) == 0)
	{
		new_node = toklist_new(PIPE, NULL);
		if (new_node == NULL)
			return (2);
		(*i) += 1;
		ft_lstadd_back((t_list **)lst_head, (t_list *)new_node);
		return (0);
	}
	return (1);
}
