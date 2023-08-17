/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_analize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:24:55 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/17 18:36:14 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_bool	is_valid_env(char c)
{
	return (
		ft_isalpha(c)
		|| c == '_'
	);
}

t_bool	is_all_valid_env(char *str)
{
	t_uint64	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_valid_env(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
