/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_env_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:55:31 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/26 16:54:07 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static t_env_list	*lstenv_new(char *key, char *val, t_bool is_export);
static t_bool		is_env_key_equal(void *v_entry, void *v_key);

void				free_entry(void *v_entry);

t_env_list	*lstenv_chr(const char *key, t_bool create)
{
	t_env_list	*founded;
	char		*duped_key;

	founded = (t_env_list *)lst_chr(*((t_list **)get_lstenv()),
			&is_env_key_equal, (void *)key);
	if (create == false || founded != NULL)
		return (founded);
	duped_key = ft_strdup(key);
	if (duped_key != NULL)
	{
		founded = lstenv_new(duped_key, NULL, false);
		if (founded != NULL)
		{
			ft_lstadd_back((t_list **)get_lstenv(), (t_list *)founded);
			return (founded);
		}
		free(duped_key);
	}
	return (NULL);
}

void	delete_entry(const char *key)
{
	lst_delif((t_list **)(get_lstenv()), &free_entry, &is_env_key_equal,
		(void *)key);
}

void	free_entry(void *v_entry)
{
	t_env_entry	*entry;

	entry = (t_env_entry *)v_entry;
	free(entry->key);
	free(entry->value);
	free(entry);
}

static t_env_list	*lstenv_new(char *key, char *val, t_bool is_export)
{
	t_env_list	*new_node;

	new_node = (t_env_list *)ft_lstnew(NULL);
	if (new_node != NULL)
	{
		new_node->data = malloc(sizeof(t_env_entry));
		if (new_node->data != NULL)
		{
			new_node->data->key = key;
			new_node->data->value = val;
			new_node->data->is_export = is_export;
			return (new_node);
		}
		free(new_node);
	}
	return (NULL);
}

static t_bool	is_env_key_equal(void *v_entry, void *v_key)
{
	t_env_entry	*entry;
	char		*key;

	entry = (t_env_entry *)v_entry;
	key = (char *)v_key;
	return (str_cmp(entry->key, key) == 0);
}
