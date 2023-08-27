/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_substitution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:17:04 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/27 10:56:37 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "environment.h"

static int	substitute_string(char **dst, char *src, size_t len);
static int	substitute_last_error(char **dst);
static int	substitute_empty(char **dst);

int	add_pre_token_subst(char *str, size_t len, t_pre_toklist **list)
{
	int				error;
	char			*substitued_str;
	t_pre_toklist	*new_node;

	if (len == 1 && ft_isdigit(str[0]))
		error = substitute_empty(&substitued_str);
	else if (len == 1 && str[0] == '?')
		error = substitute_last_error(&substitued_str);
	else
		error = substitute_string(&substitued_str, str, len);
	if (error != 0)
		return (error);
	new_node = toklist_new(TEXT, substitued_str);
	if (new_node == NULL)
		return (MALLOC_ERROR);
	ft_lstadd_back((t_list **)list, (t_list *)new_node);
	return (0);
}

static int	substitute_string(char **dst, char *src, size_t len)
{
	char	*key;
	int		error;

	key = ft_substr(src, 0, len);
	if (key == NULL)
		return (MALLOC_ERROR);
	*dst = get_env(key, &error);
	free(key);
	if (error != 0)
		return (error);
	if (*dst == NULL)
		*dst = ft_strdup("");
	if (*dst == NULL)
		return (MALLOC_ERROR);
	return (0);
}

static int	substitute_last_error(char **dst)
{
	*dst = ft_itoa(get_last_error());
	if (*dst == NULL)
		return (MALLOC_ERROR);
	return (0);
}

static int	substitute_empty(char **dst)
{
	*dst = ft_strdup("");
	if (*dst == NULL)
		return (MALLOC_ERROR);
	return (0);
}
