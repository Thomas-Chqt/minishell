/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:37:37 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/06 14:53:20 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	init_env(char *envp[])
{
	t_uint64	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (set_env2(envp[i], true) != 0)
		{
			clean_env();
			return (1);
		}
		i++;
	}
	return (0);
}

int	set_env(const char *key, const char *val, t_bool exported)
{
	t_env_list	*found;

	if (key == NULL || key[0] == '\0')
		return (1);
	found = (t_env_list *)lst_chr((t_list *)*(get_lstenv()),
			&is_env_key_equal, (void *)key);
	if (found == NULL)
	{
		found = lst_env_new(key, val, exported);
		if (found == NULL)
			return (MALLOC_ERROR);
		ft_lstadd_back((t_list **)get_lstenv(), (t_list *)found);
		return (0);
	}
	found->data->is_export = exported;
	free_null((void **)&found->data->value);
	if (val == NULL)
		return (0);
	found->data->value = ft_strdup(val);
	if (found->data->value == NULL)
		return (2);
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

int	export_env(const char *key)
{
	t_env_list	*found;

	if (key == NULL)
		return (1);
	found = (t_env_list *)lst_chr((t_list *)*(get_lstenv()),
			&is_env_key_equal, (void *)key);
	if (found == NULL)
		return (set_env(key, NULL, true));
	found->data->is_export = true;
	return (0);
}

void	clean_env(void)
{
	ft_lstclear((t_list **)get_lstenv(), &del_env_entry);
}
