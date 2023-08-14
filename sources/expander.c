/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:31:43 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/14 13:55:23 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*join_lst(t_exp_toklst *list);

int	expand_ast(t_ast *ast)
{
	if (ast == NULL)
		return (0);
	if (ast->data != NULL && ast->data->type == TEXT)
	{
		if (expand_string(&ast->data->data) != 0)
			return (1);
	}
	if (expand_ast(ast->right) != 0)
		return (1);
	if (expand_ast(ast->left) != 0)
		return (1);
	return (0);
}

int	expand_string(char **str_ptr)
{
	t_exp_toklst	*token_list;
	int				return_val;

	token_list = make_exp_toklst(*str_ptr);
	if (token_list == NULL)
		return (MALLOC_ERROR);
	return_val = substitute_toklist(token_list);
	if (return_val == 0)
	{
		free(*str_ptr);
		*str_ptr = join_lst(token_list);
		free_exp_toklst(&token_list);
		if (*str_ptr == NULL)
			return (MALLOC_ERROR);
		return (0);
	}
	free_exp_toklst(&token_list);
	return (return_val);
}

int	expand_dquote_string(char **str_ptr)
{
	t_exp_toklst	*token_list;
	int				return_val;

	token_list = make_exp_toklst_no_quote(*str_ptr);
	if (token_list == NULL)
		return (MALLOC_ERROR);
	return_val = substitute_toklist_no_print(token_list);
	if (return_val == 0)
	{
		free(*str_ptr);
		*str_ptr = join_lst(token_list);
		free_exp_toklst(&token_list);
		if (*str_ptr == NULL)
			return (MALLOC_ERROR);
		return (0);
	}
	free_exp_toklst(&token_list);
	return (return_val);
}

static char	*join_lst(t_exp_toklst *list)
{
	t_uint64		str_len;
	char			*str;
	t_exp_toklst	*watched;

	str_len = 0;
	watched = list;
	while (watched != NULL)
	{
		str_len += ft_strlen(watched->data->str);
		watched = watched->next;
	}
	str = ft_calloc(str_len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	watched = list;
	while (watched != NULL)
	{
		ft_strlcat(str, watched->data->str, str_len + 1);
		watched = watched->next;
	}
	return (str);
}
