/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:27:31 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/08 02:18:53 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env_list	**get_lstenv(void)
{
	static t_env_list	*env_list = NULL;

	return (&env_list);
}

t_env_list	*lst_env_new(const char *keyval, t_bool is_export)
{
	t_env_list	*new_node;

	new_node = malloc(sizeof(t_env_list));
	if (new_node != NULL)
	{
		new_node->data = malloc(sizeof(t_env_entry));
		if (new_node->data != NULL)
		{	
			new_node->data->is_export = is_export;
			*(new_node->data) = str_to_env_entry(keyval);
			if (new_node->data->key != NULL)
				return (new_node);
		}
		free(new_node);
	}
	return (NULL);
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
	char	*temp_str;
	char	*output;

	if (entry.value == NULL || entry.key == NULL)
		return (ft_strdup(entry.key));
	temp_str = ft_strjoin(entry.key, "=");
	if (temp_str == NULL)
		return (NULL);
	output = ft_strjoin(temp_str, entry.value);
	free(temp_str);
	return (output);
}

t_env_entry	str_to_env_entry(const char *str)
{
	char	*key;
	char	*val;

	if (str == NULL || ft_strchr(str, '=') == NULL)
		return ((t_env_entry){.key = ft_strdup(str), .value = NULL});
	if (str[0] == '=')
		return ((t_env_entry){.key = NULL, .value = NULL});
	key = ft_substr(str, 0, ft_strchr(str, '=') - str);
	if (key == NULL)
		return ((t_env_entry){.key = NULL, .value = NULL});
	val = ft_strdup(ft_strchr(str, '=') + 1);
	if (val == NULL)
		free_null((void *)&key);
	return ((t_env_entry){.key = key, .value = val});
}
