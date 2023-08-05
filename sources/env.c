/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:37:37 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/05 00:08:59 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	init_env(char *envp[])
{
	t_uint64	i;
	char		**splited_str;

	*(env_get_dict()) = dicstrenv_new(1024);
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
	return (
		dicstrenv_set(*(env_get_dict()), key, (t_env_entry){
			.is_export = exported,
			.value = (char *)val})
		);
}

char	*get_env(const char *key)
{
	t_env_entry	entry;

	entry = dicstrenv_get(*(env_get_dict()), key);
	return (entry.value);
}

void	clean_env(void)
{
	dic_clear(*(env_get_dict()));
}

t_dictionary	*env_get_dict(void)
{
	static t_dictionary	env_dict;

	return (&env_dict);
}
