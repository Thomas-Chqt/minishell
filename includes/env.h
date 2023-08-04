/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:26:37 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/04 12:31:37 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef enum e_env_action	t_env_action;
typedef struct s_env_entry	t_env_entry;

enum e_env_action 
{
	init,
	set,
	get,
	clean
};

struct s_env_entry
{
	char	*value;
	t_bool	is_export;
};

t_uint64		hash_func(void *key_ptr, size_t dict_size);
void			*dup_key_func(void *ptr);
void			*dup_val_func(void *ptr);
void			free_val_func(void *ptr);
t_bool			is_env_entry_equal_func(void *a, void *b);


t_dictionary	dicstrenv_new(size_t size);
int				dicstrenv_set(t_dictionary dict, const char *key, t_env_entry val);
t_env_entry		dicstrenv_get(t_dictionary dict, const char *key);

int				env_internal(const char *key, t_env_entry val,
					t_env_entry *result, t_env_action action);

#endif // ENV_H