/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:27:31 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/05 20:11:40 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envvar.h"

t_env_entry	*env_entry_new(const char *key, const char *val)
{
	t_env_entry	*new_entry;

	new_entry = malloc(sizeof(t_env_entry));
	if (new_entry == NULL)
		return (NULL);
	new_entry->key = ft_strdup(key);
	new_entry->value = ft_strdup(val);
	if ((new_entry->key == NULL && key != NULL)
		|| (new_entry->value == NULL && val != NULL))
	{
		free(new_entry->key);
		free(new_entry->value);
		free(new_entry);
		return (NULL);
	}
	return (new_entry);
}

void	del_env_entry(void *v_entry)
{
	t_env_entry	*entry;

	entry = (t_env_entry *)v_entry;
	free(entry->key);
	free(entry->value);
	free(entry);
}

t_list	**get_lstenv(void)
{
	static t_list	*env_list = NULL;

	return (&env_list);
}

t_bool	is_env_key_equal(void *v_entry, void *v_key)
{
	t_env_entry	*entry;
	char		*key;

	entry = (t_env_entry *)v_entry;
	key = (char *)v_key;
	return (ft_strncmp(entry->key, key, ft_strlen(key)));
}