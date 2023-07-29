/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:37:37 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/27 16:34:31 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define INIT 10
#define SET 11
#define GET 12
#define CLEAN 13

static char	*internal_func(const char *key, const char *val, int action);

int	init_env(char *envp[])
{
	t_uint64	i;
	char		*splited_str[2];

	if (internal_func(NULL, NULL, INIT) != NULL)
		return (1);
	i = 0;
	while (envp[i] != NULL)
	{
		splited_str[0] = ft_substr(envp[i], 0,
				ft_strchr(envp[i], '=') - envp[i]);
		splited_str[1] = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (splited_str[0] == NULL || splited_str[1] == NULL
			|| internal_func((const char *)splited_str[0],
				(const char *)splited_str[1], SET) != NULL)
		{
			(void)internal_func(NULL, NULL, CLEAN);
			free(splited_str[0]);
			free(splited_str[1]);
			return (3);
		}
		free(splited_str[0]);
		free(splited_str[1]);
		i++;
	}
	return (0);
}

int	set_env(const char *key, const char *val)
{
	if (internal_func(key, val, SET) != NULL)
		return (1);
	return (0);
}

char	*get_env(const char *key)
{
	return (internal_func(key, NULL, GET));
}

void	clean_env(void)
{
	(void)internal_func(NULL, NULL, CLEAN);
}

static char	*internal_func(const char *key, const char *val, int action)
{
	static t_dictionary	dict;

	if (action == INIT)
	{
		dict = dicstrstr_new(1024);
		if (dict == NULL)
			return ((char *)1);
		return (NULL);
	}
	if (action == SET)
	{
		if (dicstrstr_set(dict, (char *)key, (char *)val) != 0)
			return ((char *)1);
		return (NULL);
	}
	if (action == GET)
		return (dicstrstr_get(dict, (char *)key));
	if (action == CLEAN)
	{
		dic_clear(dict);
		return (NULL);
	}
	return ((char *)1);
}
