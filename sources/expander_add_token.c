/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_add_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:30:08 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/14 14:04:33 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	exp_add_env(char *str, t_uint64 *i, t_exp_toklst **list)
{
	if (str[*i] != '$')
		return (PARSING_ERROR);
	if (str[*i + 1] == '?')
		return (exp_add_last_err(str, i, list));
	if (str[*i + 1] == 123)
		return (exp_add_env_brake(str, i, list));
	if (is_valid_env(str[*i + 1]))
		return (exp_add_env_no_brake(str, i, list));
	return (PARSING_ERROR);
}

int	exp_add_dquote(char *str, t_uint64 *i, t_exp_toklst **list)
{
	char			*next_quote;
	t_exp_toklst	*new_node;

	if (str[*i] != '\"')
		return (PARSING_ERROR);
	(*i)++;
	next_quote = ft_strchr(str + *i, '\"');
	if (next_quote == NULL)
		return (PARSING_ERROR);
	new_node = exp_toklst_new(str + *i, next_quote - (str + *i), dquote);
	if (new_node == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	*i += (next_quote - (str + *i)) + 1;
	return (0);
}

int	exp_add_quote(char *str, t_uint64 *i, t_exp_toklst **list)
{
	char			*next_quote;
	t_exp_toklst	*new_node;

	if (str[*i] != '\'')
		return (PARSING_ERROR);
	(*i)++;
	next_quote = ft_strchr(str + *i, '\'');
	if (next_quote == NULL)
		return (PARSING_ERROR);
	new_node = exp_toklst_new(str + *i, next_quote - (str + *i), normal);
	if (new_node == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	*i += (next_quote - (str + *i)) + 1;
	return (0);
}

int	exp_add_normal(char *str, t_uint64 *i, t_exp_toklst **list)
{
	t_uint64		tok_start;
	t_exp_toklst	*new_node;

	tok_start = (*i)++;
	while (ft_strchr("$\"\'\0", str[*i]) == NULL)
		(*i)++;
	new_node = exp_toklst_new(str + tok_start, *i - tok_start, normal);
	if (new_node == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

int	exp_add_normal_no_quote(char *str, t_uint64 *i, t_exp_toklst **list)
{
	t_uint64		tok_start;
	t_exp_toklst	*new_node;

	tok_start = (*i)++;
	while (ft_strchr("$\0", str[*i]) == NULL)
		(*i)++;
	new_node = exp_toklst_new(str + tok_start, *i - tok_start, normal);
	if (new_node == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}
