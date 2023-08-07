/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:27:31 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/06 15:51:24 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env_list	*lst_env_new(const char *key, const char *val, t_bool is_export)
{
	t_env_list	*new_node;

	new_node = malloc(sizeof(t_env_list));
	if (new_node != NULL)
	{
		new_node->next = NULL;
		new_node->data = ft_calloc(1, sizeof(t_env_entry));
		if (new_node->data != NULL)
		{
			new_node->data->is_export = is_export;
			new_node->data->key = ft_strdup(key);
			if (new_node->data->key != NULL)
			{
				if (val == NULL)
					return (new_node);
				new_node->data->value = ft_strdup(val);
				if (new_node->data->value != NULL)
					return (new_node);
				free(new_node->data->key);
			}
			free(new_node->data);
		}
		free(new_node);
	}
	return (NULL);
}

void	del_env_entry(void *v_entry)
{
	t_env_entry	*entry;

	entry = (t_env_entry *)v_entry;
	free(entry->key);
	free(entry->value);
	free(entry);
}

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

int	set_env2(const char *keyval, t_bool exported)
{
	char	**splited_str;
	int		retval;

	splited_str = str_split_on_first(keyval, '=');
	retval = set_env(splited_str[0], splited_str[1], exported);
	free_splited_str(splited_str);
	return (retval);
}
