/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:31:43 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/20 16:42:14 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	expand_string(char **str_ptr);
static char	*join_lst(t_str_list *list);

int	expand_ast(t_ast *ast)
{
	int	temp_ret;

	if (ast == NULL)
		return (0);
	if (ast->data != NULL && ast->data->type == TEXT)
	{
		temp_ret = expand_string(&ast->data->data);
		if (temp_ret != 0)
		{
			if (temp_ret == BAD_SUBSTITUTION)
				set_last_error(1);
			else
				set_last_error(temp_ret);
			return (temp_ret);
		}
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
		temp_ret = add_next_str(*str_ptr, &i, &str_list, false);
		if (temp_ret != 0)
			break ;
	}
	if ((*str_ptr)[i] != '\0')
	{
		ft_lstclear((t_list **)&str_list, &free_wrap);
		return (temp_ret);
	}
	free(*str_ptr);
	*str_ptr = join_lst(str_list);
	ft_lstclear((t_list **)&str_list, &free_wrap);
	if (*str_ptr == NULL)
		return (MALLOC_ERROR);
	return (0);
}

static char	*join_lst(t_str_list *list)
{
	t_uint64	str_len;
	char		*str;
	t_str_list	*watched;

	str_len = 0;
	watched = list;
	while (watched != NULL)
	{
		str_len += ft_strlen(watched->str);
		watched = watched->next;
	}
	str = ft_calloc(str_len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	watched = list;
	while (watched != NULL)
	{
		ft_strlcat(str, watched->str, str_len + 1);
		watched = watched->next;
	}
	return (str);
}
