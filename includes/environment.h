/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:26:37 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/28 15:28:58 by tchoquet         ###   ########.fr       */
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
void		clear_env(void);

int			set_env(const char *key, const char *val, t_bool export);
char		*get_env(const char *key, int *error_code);
int			delete_env(const char *key);
char		**get_envp(void);
int			export_env(const char *key);

int			set_env_single_str(const char *keyval, t_bool export);
char		*get_env_create(const char *keyval, int *error_code);

void		set_last_error(int code);
int			get_last_error(void);
char		*get_default_home(void);

t_env_list	**get_lstenv(void);
int			is_valid_keyval(const char *str);
size_t		valid_key_len(const char *str);

#endif // ENVIRONMENT_H