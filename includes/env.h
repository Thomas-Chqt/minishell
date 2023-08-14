/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:26:37 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/14 16:35:10 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "error.h"

typedef struct s_env_entry	t_env_entry;
typedef struct s_env_list	t_env_list;

struct s_env_entry
{
	char	*key;
	char	*value;
	t_bool	is_export;
};

struct s_env_list
{
	t_env_entry	*data;
	t_env_list	*next;
};

char		*get_env(const char *key);
char		**get_envp(void);
int			set_env(const char *keyval, t_bool exported);

t_env_list	**get_lstenv(void);
t_env_list	*lst_env_new(const char *keyval, t_bool is_export);
t_bool		is_env_key_equal(void *entry, void *key);
char		*env_entry_to_str(t_env_entry entry);
t_env_entry	str_to_env_entry(const char *str);

t_bool		is_valid_env(char c);
t_bool		is_all_valid_env(char *str);

#endif // ENV_H