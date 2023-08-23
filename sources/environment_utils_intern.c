/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_intern.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:14:55 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/24 14:22:56 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_bool	is_valid_env_key(const char *str)
{
	size_t	key_len;

	key_len = valid_key_len(str);
	if (key_len == 0 || str[key_len - 1] != '\0')
		return (false);
	return (true);
}

char	*set_error_return(int *error, int value)
{
	if (error != NULL)
		*error = value;
	return (NULL);
}

char	*env_entry_to_str(t_env_entry entry)
{
	char	*output;
	size_t	output_len;

	output_len = ft_strlen(entry.key) + ft_strlen(entry.value);
	output_len += (entry.key != NULL && entry.value != NULL);
	output = ft_calloc(output_len + 1, sizeof(char));
	if (output == NULL)
		return (NULL);
	ft_strlcat(output, entry.key, output_len + 1);
	if (entry.key != NULL && entry.value != NULL)
		ft_strlcat(output, "=", output_len + 1);
	ft_strlcat(output, entry.value, output_len + 1);
	return (output);
}

t_env_entry	str_to_env_entry(const char *str)
{
	char	*key;
	char	*val;
	char	*equal_pos;

	equal_pos = ft_strchr(str, '=');
	if (equal_pos == NULL)
		return ((t_env_entry){.key = ft_strdup(str), .value = NULL});
	key = ft_substr(str, 0, equal_pos - str);
	if (key == NULL)
		return ((t_env_entry){.key = NULL, .value = NULL});
	val = ft_strdup(equal_pos + 1);
	if (val == NULL)
	{
		free(key);
		return ((t_env_entry){.key = NULL, .value = NULL});
	}
	return ((t_env_entry){.key = key, .value = val});
}