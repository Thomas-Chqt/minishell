/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:24:55 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/28 11:47:42 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_list	**get_lstenv(void)
{
	static t_env_list	*env_list = NULL;

	return (&env_list);
}

size_t	valid_key_len(const char *str)
{
	size_t	len;

	len = 0;
	if (!ft_isalpha(str[len]) && str[len] != '_')
		return (0);
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

int	is_valid_keyval(const char *str)
{
	size_t	key_len;

	key_len = valid_key_len(str);
	if (str[key_len] == '\0')
		return (NULL_ENVIRONMENT_VAL);
	if (key_len == 0 || str[key_len] != '=')
		return (BAD_ENVIRONMENT_KEY);
	return (0);
}
