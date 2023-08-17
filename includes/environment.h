/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:26:37 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/17 19:25:48 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

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

int			init_env(char *envp[]);
int			set_env(const char *key, const char *val, t_bool exported);
int			set_env_single_str(const char *keyval, t_bool exported);
char		*get_env(const char *key);
char		**get_envp(void);

int			set_last_error(int code);
int			get_last_error(void);

t_env_list	*lstenv_new(const char *key, const char *val, t_bool is_export);
t_env_list	*lstenv_new_single_str(const char *keyval, t_bool is_export);
t_env_list	*lstenv_chr(const char *key);
void		lstenv_add_back(t_env_list	*new_node);
void		lstenv_clear(void);

t_env_list	**get_lstenv(void);
t_bool		is_env_key_equal(void *entry, void *key);
char		*env_entry_to_str(t_env_entry entry);
t_env_entry	str_to_env_entry(const char *str);

t_bool		is_valid_env(char c);
t_bool		is_all_valid_env(char *str);

#endif // ENVIRONMENT_H