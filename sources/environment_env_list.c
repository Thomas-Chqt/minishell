/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_env_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:55:31 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/18 17:21:23 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_list	**get_lstenv(void);
t_bool		is_env_key_equal(void *entry, void *key);
char		*env_entry_to_str(t_env_entry entry);
t_env_entry	str_to_env_entry(const char *str);

t_env_list	*lstenv_new(char *key, char *val, t_bool is_export)
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

t_env_list	*lstenv_new_single_str(const char *keyval, t_bool is_export)
{
	t_env_list	*new_node;

	new_node = (t_env_list *)ft_lstnew(NULL);
	if (new_node != NULL)
	{
		new_node->data = malloc(sizeof(t_env_entry));
		if (new_node->data != NULL)
		{	
			*(new_node->data) = str_to_env_entry(keyval);
			new_node->data->is_export = is_export;
			if (new_node->data->key != NULL)
				return (new_node);
		}
		free(new_node);
	}
	return (NULL);
}

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

void	lstenv_add_back(t_env_list	*new_node)
{
	ft_lstadd_back((t_list **)get_lstenv(), (t_list *)new_node);
}

void	lstenv_clear(void)
{
	t_env_list	*watched;
	t_env_list	*temp;

	watched = *(get_lstenv());
	while (watched != NULL)
	{
		free(watched->data->key);
		free(watched->data->value);
		free(watched->data);
		temp = watched->next;
		free(watched);
		watched = temp;
	}
	(*(get_lstenv())) = NULL;
}
