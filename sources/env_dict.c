/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dict.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:45:11 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/05 14:18:22 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_dictionary	dicstrenv_new(size_t size)
{
	t_dictionary	new_dict;

	new_dict = dic_new(size, &hash_func);
	dic_setdupfunc(new_dict, &dup_key_func, &dup_val_func);
	dic_setfreefunc(new_dict, &free_str_ptr, &free_val_func);
	return (new_dict);
}

int	dicstrenv_set(t_dictionary dict, const char *key, t_env_entry val)
{
	return (dic_set(dict, (void *)&key, (void *)&val,
			&is_env_entry_equal_func));
}

t_env_entry	dicstrenv_get(t_dictionary dict, const char *key)
{
	t_env_entry	*entry_ptr;
	t_env_entry	entry;

	entry_ptr = (t_env_entry *)dic_get(dict, (void *)&key,
			&is_env_entry_equal_func);
	if (entry_ptr == NULL)
		return ((t_env_entry){.value = NULL});
	entry = *entry_ptr;
	free(entry_ptr);
	return (entry);
}
