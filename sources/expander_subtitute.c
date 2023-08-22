/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_subtitute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:08:40 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/22 11:18:13 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	substitute_str(char **dest, char *src, size_t len);

int	add_substitued(char *str, size_t len, t_str_list **list)
{
	t_str_list	*new_node;
	int			temp_ret;

	new_node = (t_str_list *)ft_lstnew(NULL);
	if (new_node == NULL)
		return (MALLOC_ERROR);
	temp_ret = substitute_str(&new_node->str, str, len);
	if (temp_ret != 0)
	{
		free(new_node);
		return (temp_ret);
	}
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

static int	substitute_str(char **dest, char *src, size_t len)
{
	int		error;
	char	*subed_str;

	subed_str = ft_substr(src, 0, len);
	if (subed_str == NULL)
		return (MALLOC_ERROR);
	*dest = get_env_create(subed_str, &error);
	if (error == NULL_ENVIRONMENT_VAL)
		*dest = get_env(subed_str, &error);
	if (*dest == NULL && error == 0)
		*dest = ft_strdup("");
	if (*dest == NULL)
		error = MALLOC_ERROR;
	free(subed_str);
	return (error);
}
