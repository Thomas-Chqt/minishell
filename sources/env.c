/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:37:37 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/04 14:11:54 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	init_env(char *envp[])
{
	t_uint64	i;
	char		**splited_str;

	if (env_internal(NULL, (t_env_entry){}, NULL, init) != 0)
		return (1);
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
	if (ft_strlen(key) == 0)
		return (1);
	if (ft_strlen(val) == 0)
		return (1);
	return (env_internal(key, (t_env_entry){
			.is_export = exported,
			.value = (char *)val}, NULL, set));
}

char	*get_env(const char *key)
{
	t_env_entry	entry;

	env_internal(key, (t_env_entry){}, &entry, get);
	return (entry.value);
}

void	clean_env(void)
{
	(void)env_internal(NULL, (t_env_entry){}, NULL, clean);
}

int	env_internal(const char *key, t_env_entry val,
		t_env_entry *result, t_env_action action)
{
	static t_dictionary	dict;

	if (action == init)
	{
		dict = dicstrenv_new(1024);
		if (dict == NULL)
			return (1);
	}
	else if (action == set)
	{
		if (dicstrenv_set(dict, key, val) != 0)
			return (1);
	}
	else if (action == get)
		*result = dicstrenv_get(dict, key);
	else if (action == clean)
		dic_clear(dict);
	return (0);
}
