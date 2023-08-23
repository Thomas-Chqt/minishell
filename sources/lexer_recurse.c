/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_recurse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:35:46 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/23 18:41:21 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			recurse_full_cmd(const char *cmd, t_uint64 *i, t_toklist **list);
static int	recurse_simple_cmd(const char *cmd, t_uint64 *i, t_toklist **list);
static int	recurse_io_list(const char *cmd, t_uint64 *i, t_toklist **list);
static int	recurse_io_file(const char *cmd, t_uint64 *i, t_toklist **list);
static int	recurse_text_list(const char *cmd, t_uint64 *i, t_toklist **list);

int			toklist_text_new(const char *cmd, t_uint64 *i, t_toklist **list);
int			toklist_pipe_new(const char *cmd, t_uint64 *i, t_toklist **list);
int			toklist_io_new(const char *cmd, t_uint64 *i, t_toklist **list);

int	recurse_full_cmd(const char *cmd, t_uint64 *i, t_toklist **list)
{
	t_toklist	*new_list;
	int			error;

	new_list = NULL;
	error = recurse_simple_cmd(cmd, i, &new_list);
	if (error != 0)
		return (error);
	while (cmd[*i] == ' ')
		(*i)++;
	if (cmd[*i] != '\0')
	{
		error = toklist_pipe_new(cmd, i, &new_list);
		if (error == 0)
		{
			while (cmd[*i] == ' ')
				(*i)++;
			error = recurse_full_cmd(cmd, i, &new_list);
		}
	}
	if (error != 0)
		ft_lstclear((t_list **)new_list, &free_token);
	else
		ft_lstadd_back((t_list **)list, (t_list *)new_list);
	return (error);
}

static int	recurse_simple_cmd(const char *cmd, t_uint64 *i, t_toklist **list)
{
	t_toklist	*new_list;
	int			error;

	new_list = NULL;
	error = recurse_io_list(cmd, i, &new_list);
	if (error != 0 && error != PARSING_ERROR)
		return (error);
	while (cmd[*i] == ' ')
		(*i)++;
	error = recurse_text_list(cmd, i, &new_list);
	if (error == 0 || error == PARSING_ERROR)
	{
		while (cmd[*i] == ' ')
			(*i)++;
		error = recurse_io_list(cmd, i, &new_list);
		if (error == 0 || error == PARSING_ERROR)
		{
			if (new_list == NULL)
				return (PARSING_ERROR);
			ft_lstadd_back((t_list **)list, (t_list *)new_list);
			return (0);
		}
	}
	ft_lstclear((t_list **)new_list, &free_token);
	return (error);
}

static int	recurse_io_list(const char *cmd, t_uint64 *i, t_toklist **list)
{
	t_toklist	*new_list;
	int			error;

	new_list = NULL;
	error = recurse_io_file(cmd, i, &new_list);
	if (error == 0)
	{
		while (cmd[*i] == ' ')
			(*i)++;
		error = recurse_io_list(cmd, i, &new_list);
		if (error == 0 || error == PARSING_ERROR)
		{
			ft_lstadd_back((t_list **)list, (t_list *)new_list);
			return (0);
		}
		ft_lstclear((t_list **)new_list, &free_token);
	}
	return (error);
}

static int	recurse_io_file(const char *cmd, t_uint64 *i, t_toklist **list)
{
	t_toklist	*new_list;
	int			error;
	t_uint64	save_i;

	save_i = (*i);
	new_list = NULL;
	error = toklist_io_new(cmd, i, &new_list);
	if (error == 0)
	{
		while (cmd[*i] == ' ')
			(*i)++;
		error = toklist_text_new(cmd, i, &new_list);
		if (error == 0)
		{
			ft_lstadd_back((t_list **)list, (t_list *)new_list);
			return (0);
		}
		ft_lstclear((t_list **)new_list, &free_token);
		(*i) = save_i;
	}
	return (error);
}

static int	recurse_text_list(const char *cmd, t_uint64 *i, t_toklist **list)
{
	t_toklist	*new_list;
	int			error;

	new_list = NULL;
	error = toklist_text_new(cmd, i, &new_list);
	if (error == 0)
	{
		while (cmd[*i] == ' ')
			(*i)++;
		error = recurse_text_list(cmd, i, &new_list);
		if (error == 0 || error == PARSING_ERROR)
		{
			ft_lstadd_back((t_list **)list, (t_list *)new_list);
			return (0);
		}
		ft_lstclear((t_list **)new_list, &free_token);
	}
	return (error);
}
