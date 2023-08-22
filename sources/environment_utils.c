/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:24:55 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/22 15:19:26 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_entry		str_to_env_entry(const char *str);

t_bool	is_valid_env_key(const char *str)
{
	t_uint64	i;

	if (str == NULL)
		return (false);
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	if (i == 0)
		return (false);
	return (true);
}

int	analize_keyval(const char *keyval, t_env_entry *result)
{
	t_env_entry	input;

	input = str_to_env_entry(keyval);
	if (input.key == NULL)
		return (MALLOC_ERROR);
	if (is_valid_env_key(input.key) == false)
	{
		free(input.key);
		free(input.value);
		return (BAD_ENVIRONMENT_KEY);
	}
	if (input.value == NULL)
	{
		free(input.key);
		free(input.value);
		return (NULL_ENVIRONMENT_VAL);
	}
	*result = input;
	return (0);
}

char	*set_error_return(int *error, int value)
{
	if (error != NULL)
		*error = value;
	return (NULL);
}

t_bool	is_valid_keyval(const char *str)
{
	t_uint64	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	if (str[i] != '=')
		return (false);
	return (true);
}
