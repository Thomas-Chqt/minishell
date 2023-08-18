/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_env_list_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:27:31 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/18 17:03:51 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_list	**get_lstenv(void)
{
	static t_env_list	*env_list = NULL;

	return (&env_list);
}

t_bool	is_env_key_equal(void *v_entry, void *v_key)
{
	t_env_entry	*entry;
	char		*key;

	entry = (t_env_entry *)v_entry;
	key = (char *)v_key;
	return (str_cmp(entry->key, key) == 0);
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
