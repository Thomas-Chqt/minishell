/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_env_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:55:31 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/17 19:19:12 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_list	*lstenv_new(const char *key, const char *val, t_bool is_export)
{

}

t_env_list	*lstenv_new_single_str(const char *keyval, t_bool is_export)
{
	t_env_list	*new_node;

	new_node = malloc(sizeof(t_env_list));
	if (new_node != NULL)
	{
		new_node->next = NULL;
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

t_env_list	*lstenv_chr(const char *key)
{

}

void	lstenv_add_back(t_env_list	*new_node)
{

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