/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_add_token_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 19:00:29 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/14 13:24:06 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	exp_add_last_err(char *str, t_uint64 *i, t_exp_toklst **list)
{
	t_exp_toklst	*new_node;

	new_node = exp_toklst_new("?", 1, substit);
	if (new_node == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	*i += 2;
	return (0);
}

int	exp_add_env_brake(char *str, t_uint64 *i, t_exp_toklst **list)
{
	char			*next_brake;
	t_exp_toklst	*new_node;

	next_brake = ft_strchr(str + *i + 2, 125);
	if (next_brake == NULL)
		return (PARSING_ERROR);
	*i += 2;
	new_node = exp_toklst_new(str + *i, next_brake - (str + *i), substit);
	if (new_node == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	*i += (next_brake - (str + *i)) + 1;
	return (0);
}

int	exp_add_env_no_brake(char *str, t_uint64 *i, t_exp_toklst **list)
{
	t_uint64		tok_start;
	t_exp_toklst	*new_node;

	tok_start = ++(*i);
	while (is_valid_env(str[*i]))
		(*i)++;
	new_node = exp_toklst_new(str + tok_start, *i - tok_start, substit);
	if (new_node == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}
