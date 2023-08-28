/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_add_pre_token2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:01:24 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/28 15:46:41 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "environment.h"

int	add_pre_token_subst(char *str, size_t len, t_pre_toklist **list);

int	add_pre_token_tilde(char *str, t_uint64 *i, t_pre_toklist **list)
{
	int				error;
	char			*current_home;
	t_pre_toklist	*new_node;

	if (*i != 0)
		return (PARSING_ERROR);
	if (ft_memcmp(str, "~\0", 2) != 0 && ft_memcmp(str, "~/", 2) != 0)
		return (PARSING_ERROR);
	current_home = get_env("HOME", &error);
	if (error != 0)
		return (error);
	if (current_home == NULL)
		current_home = ft_strdup(get_default_home());
	new_node = toklist_new(TEXT, current_home);
	if (new_node == NULL)
		return (MALLOC_ERROR);
	(*i)++;
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

int	add_pre_token_normal(char *str, t_uint64 *i, t_pre_toklist **list)
{
	size_t			token_len;
	t_pre_toklist	*new_node;

	token_len = 1;
	while ((str + *i)[token_len] != '\0'
			&& (str + *i)[token_len] != '\''
			&& (str + *i)[token_len] != '\"'
			&& (str + *i)[token_len] != '$')
		token_len++;
	new_node = toklist_new(TEXT, ft_substr(str, (*i), token_len));
	if (new_node == NULL)
		return (MALLOC_ERROR);
	(*i) += token_len;
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

int	add_pre_token_empty(t_pre_toklist **list)
{
	t_pre_toklist	*new_node;

	new_node = toklist_new(TEXT, ft_strdup(""));
	if (new_node == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}
