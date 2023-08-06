/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:37:37 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/05 22:44:40 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envvar.h"

int	init_env(char *envp[])
{
	t_uint64	i;
	char		**splited_str;

	i = 0;
	while (envp[i] != NULL)
	{
		splited_str = str_split_on_first(envp[i], '=');
		if (arrstr_len(splited_str) != 2
			|| set_env(splited_str[0], splited_str[1], true) != 0)
		{
			free_splited_str(splited_str);
			clean_env();
			return (1);
		}
		free_splited_str(splited_str);
		i++;
	}
	return (0);
}

int	set_env(const char *key, const char *val, t_bool exported)
{
	t_env_entry	*entry;
	t_env_entry	*new_entry;

	if (key == NULL)
		return (1);
	entry = lst_chr(*(get_lstenv()), &is_env_key_equal, key);
	if (entry == NULL)
	{
		new_entry = env_entry_new(key, val);
		if (new_entry == NULL)
			return (MALLOC_ERROR);
		ft_lstadd_back(get_lstenv(), new_entry);
		return (0);
	}
	free_null(&entry->value);
	if (val == NULL)
		return (0);
	entry->value = ft_strdup(val);
	if (entry->value == NULL)
		return (2);
	return (0);
}

char	*get_env(const char *key)
{
	t_env_entry	*entry;

	if (key == NULL)
		return (1);
	entry = lst_chr(*(get_lstenv()), &is_env_key_equal, key);
	if (entry == NULL)
		return (NULL);
	return (ft_strdup(entry->value));
}

void	clean_env(void)
{
	ft_lstclear(get_lstenv(), &del_env_entry);
}
