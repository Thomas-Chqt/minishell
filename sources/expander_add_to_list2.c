/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_add_to_list2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:28:20 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/20 17:03:27 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	exp_lstadd_last_error(char *str, t_uint64 *i, t_str_list **list)
{
	t_str_list	*new_node;

	if (str[*i] != '$' || str[(*i) + 1] != '?')
		return (PARSING_ERROR);
	new_node = (t_str_list *)ft_lstnew(NULL);
	if (new_node != NULL)
	{
		new_node->str = ft_itoa(get_last_error());
		if (new_node->str != NULL)
		{
			ft_lstadd_back((t_list **)list, (t_list *)new_node);
			*i += 2;
			return (0);
		}
		free(new_node);
	}
	return (MALLOC_ERROR);
}

int	exp_lstadd_tilde(char *str, t_uint64 *i, t_str_list **list)
{
	t_str_list	*new_node;
	int			error;

	if (*i != 0 || str[*i] != '~'
		|| (str[(*i) + 1] != '/' && str[(*i) + 1] != '\0'))
		return (PARSING_ERROR);
	new_node = (t_str_list *)ft_lstnew(NULL);
	if (new_node != NULL)
	{
		new_node->str = get_env("HOME", &error);
		if (new_node->str != NULL || error == 0)
		{
			ft_lstadd_back((t_list **)list, (t_list *)new_node);
			*i += 1;
			return (0);
		}
		free(new_node);
	}
	else
		return (MALLOC_ERROR);
	return (error);
}
