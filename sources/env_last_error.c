/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_last_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:40:39 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/14 16:33:22 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	set_last_error(int code)
{
	char	*str;
	char	*key_val;

	str = ft_itoa(code);
	if (str != NULL)
	{
		key_val = ft_calloc(ft_strlen(str) + 3, sizeof(char));
		if (key_val != NULL)
		{
			ft_strlcat(key_val, "?=", ft_strlen(str) + 3);
			ft_strlcat(key_val, str, ft_strlen(str) + 3);
			if (set_env(key_val, false) == 0)
			{
				free(key_val);
				free(str);
				return (0);
			}
			free(key_val);
		}
		free(str);
	}
	return (MALLOC_ERROR);
}

int	get_last_error(void)
{
	char	*str;
	int		code;

	str = get_env("?");
	if (str == NULL)
		return (0);
	code = ft_atoi(str);
	free(str);
	return (code);
}
