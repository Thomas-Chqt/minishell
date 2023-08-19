/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:31:43 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/19 18:32:01 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	expand_string(char **str_ptr);

int	expand_ast(t_ast *ast)
{
	int	temp_ret;

	if (ast == NULL)
		return (0);
	if (ast->data != NULL && ast->data->type == TEXT)
	{
		temp_ret = expand_string(&ast->data->data);
		if (temp_ret != 0)
			return (temp_ret);
	}
	temp_ret = expand_ast(ast->right);
	if (temp_ret != 0)
		return (temp_ret);
	temp_ret = expand_ast(ast->left);
	if (temp_ret != 0)
		return (temp_ret);
	return (0);
}

static int	expand_string(char **str_ptr)
{
	t_str_list	*str_list;
	t_uint64	i;
	int			temp_ret;

	str_list = NULL;
	i = 0;
	while ((*str_ptr)[i] != '\0')
	{
		temp_ret = exp_lstadd_bracket(*str_ptr, &i, &str_list);
		if (temp_ret == MALLOC_ERROR)
			break ;
		temp_ret = exp_lstadd_normal(*str_ptr, &i, &str_list);
		if (temp_ret == MALLOC_ERROR)
			break ;
	}
	if ((*str_ptr)[i] != '\0')
	{
		ft_lstclear((t_list **)&str_list, &free_wrap);
		return (temp_ret);
	}
	return (0);
}
