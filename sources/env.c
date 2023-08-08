/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:59:47 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/08 02:56:25 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	init_env(char *envp[])
{
	t_uint64	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (set_env(envp[i], true) != 0)
		{
			clean_env();
			return (1);
		}
		i++;
	}
	return (0);
}

char	*get_env(const char *key)
{
	t_env_list	*found;
	char		*str;

	if (key == NULL)
		return (NULL);
	found = (t_env_list *)lst_chr((t_list *)*(get_lstenv()),
			&is_env_key_equal, (void *)key);
	if (found == NULL)
		return (NULL);
	str = ft_strdup(found->data->value);
	return (str);
}

char	**get_envp(void)
{
	char		**envp;
	t_env_list	*current;
	t_uint64	i;

	current = *(get_lstenv());
	envp = ft_calloc(ft_lstsize((t_list *)current) + 1, sizeof(char *));
	if (envp == NULL)
		return (NULL);
	i = 0;
	while (current != NULL)
	{
		envp[i] = env_entry_to_str(*current->data);
		if (envp[i] == NULL)
		{
			free_splited_str(envp);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	return (envp);
}

int	set_env(const char *keyval, t_bool exported)
{
	t_env_list	*found;
	t_env_list	*new_node;

	new_node = lst_env_new(keyval, exported);
	if (new_node != NULL)
	{
		found = (t_env_list *)lst_chr(*((t_list **)get_lstenv()),
				&is_env_key_equal, new_node->data->key);
		if (found == NULL)
		{
			ft_lstadd_back((t_list **)get_lstenv(), (t_list *)new_node);
			return (0);
		}
		found->data = new_node->data;
		free(new_node);
		return (0);
	}
	return (1);
}

void	clean_env(void)
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
