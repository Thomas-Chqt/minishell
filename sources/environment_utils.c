/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:24:55 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/18 17:26:22 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static t_bool	is_valid_char(char c);

t_bool	is_valid_env_key(const char *str)
{
	t_uint64	i;

	if (str == NULL)
		return (false);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (is_valid_char(str[i]) == false)
			return (false);
		i++;
	}
	if (i == 0)
		return (false);
	return (true);
}

static t_bool	is_valid_char(char c)
{
	return (
		ft_isalpha(c)
		|| c == '_'
	);
}
