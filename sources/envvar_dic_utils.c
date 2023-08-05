/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_dic_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:13:01 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/05 14:44:03 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envvar.h"

t_uint64	hash_func(void *key_ptr, size_t dict_size)
{
	char		*key;
	t_uint64	hash;
	t_uint64	i;
	size_t		key_len;

	key = *((char **)key_ptr);
	hash = 7;
	key_len = ft_strlen(key);
	i = 0;
	while (i < key_len)
	{
		hash = (hash * 31) + key[i];
		i++;
	}
	return (hash % dict_size);
}

void	*dup_key_func(void *ptr)
{
	char	*str;
	char	*duped_str;
	char	**duped_str_ptr;

	str = *((char **)ptr);
	duped_str = ft_strdup(str);
	if (duped_str == NULL)
		return (NULL);
	duped_str_ptr = malloc(sizeof(char *));
	if (duped_str_ptr == NULL)
		free(duped_str);
	else
		*duped_str_ptr = duped_str;
	return (duped_str_ptr);
}

void	*dup_val_func(void *ptr)
{
	t_env_entry	*entry;
	t_env_entry	*duped_entry;

	entry = (t_env_entry *)ptr;
	duped_entry = malloc(sizeof(t_env_entry));
	if (duped_entry != NULL)
	{
		duped_entry->is_export = entry->is_export;
		duped_entry->value = ft_strdup((const char *)entry->value);
		if (duped_entry->value != NULL)
			return (duped_entry);
		free(duped_entry);
	}
	return (NULL);
}

void	free_val_func(void *ptr)
{
	t_env_entry	*entry;

	entry = (t_env_entry *)ptr;
	free(entry->value);
	free(entry);
}

t_bool	is_env_entry_equal_func(void *a, void *b)
{
	t_env_entry	*entry_a;
	t_env_entry	*entry_b;

	entry_a = (t_env_entry *)a;
	entry_b = (t_env_entry *)b;
	return (ft_strncmp(*((const char **)a), *((const char **)b),
			ft_strlen(*((const char **)a))) == 0);
}
