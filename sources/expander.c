/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:06:42 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/27 19:16:57 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_pre_toklist		*make_pre_toklist(t_token token, int *error);

int					add_retokenized_pre_token(t_pre_token pre_token,
						t_toklist **token_list);

static int			add_expanded_token(t_token token, t_toklist **token_list);
static int			add_duped_token(t_token token, t_toklist **token_list);
static t_toklist	*token_from_file(int fd, t_uint64 len);

int	expand_toklist(t_toklist **token_list)
{
	t_toklist	*watched;
	t_toklist	*expanded_toklist;
	int			error;

	expanded_toklist = NULL;
	watched = *token_list;
	while (watched != NULL)
	{
		if (watched->data->type == TEXT || watched->data->type == DQUOTED)
			error = add_expanded_token(*(watched->data), &expanded_toklist);
		else
			error = add_duped_token(*(watched->data), &expanded_toklist);
		if (error != 0)
			break ;
		watched = watched->next;
	}
	if (error != 0)
		ft_lstclear((t_list **)&expanded_toklist, &free_token);
	if (error == 0)
		ft_lstclear((t_list **)token_list, &free_token);
	if (error == 0)
		*token_list = expanded_toklist;
	if (error != 1)
		return (print_error(error));
	return (error);
}

int	put_expanded_file_fd(int fd_in, size_t len, int fd_out)
{
	t_toklist	*temp_token;
	int			error;

	temp_token = token_from_file(fd_in, len);
	if (temp_token == NULL)
		return (MALLOC_ERROR);
	error = expand_toklist(&temp_token);
	if (error != 0)
		return (error);
	ft_putstr_fd(temp_token->data->data, fd_out);
	ft_lstclear((t_list **)&temp_token, &free_token);
	return (0);
}

static int	add_expanded_token(t_token token, t_toklist **token_list)
{
	t_pre_toklist	*pre_toklist;
	t_pre_toklist	*watched;
	t_toklist		*retoken_list;
	int				error;

	pre_toklist = make_pre_toklist(token, &error);
	if (error != 0)
		return (error);
	retoken_list = NULL;
	watched = pre_toklist;
	while (watched != NULL)
	{
		error = add_retokenized_pre_token(*(watched->data), &retoken_list);
		if (error != 0)
			break ;
		watched = watched->next;
	}
	ft_lstclear((t_list **)&pre_toklist, &free_token);
	if (error == 0)
		ft_lstadd_back((t_list **)token_list, (t_list *)retoken_list);
	return (error);
}

static int	add_duped_token(t_token token, t_toklist **token_list)
{
	t_toklist	*duped_token;

	if (token.type >= TEXT)
		duped_token = toklist_new(TEXT, ft_strdup(token.data));
	else
		duped_token = toklist_new(token.type, ft_strdup(token.data));
	if (duped_token == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back((t_list **)token_list, (t_list *)duped_token);
	return (0);
}

static t_toklist	*token_from_file(int fd, t_uint64 len)
{
	t_toklist	*token;
	char		*file_data;
	char		*line;

	file_data = ft_calloc(len + 1, sizeof(char));
	if (file_data == NULL)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_strlcat(file_data, line, len + 1);
		free(line);
		line = get_next_line(fd);
	}
	token = toklist_new(DQUOTED, file_data);
	if (token != NULL)
		return (token);
	free(file_data);
	return (NULL);
}
