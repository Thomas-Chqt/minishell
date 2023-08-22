/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:26:37 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/22 14:28:21 by tchoquet         ###   ########.fr       */
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

t_env_list	**get_lstenv(void);

int			init_env(char *envp[]);
void		clear_env(void);

t_bool		is_valid_keyval(const char *str);

int			set_env(const char *key, const char *val, t_bool export);
int			set_env_single_str(const char *keyval, t_bool export);
char		*get_env(const char *key, int *error_code);
char		*get_env_create(const char *keyval, int *error_code);
char		**get_envp(void);
int			export_env(const char *key);
int			delete_env(const char *key);

void		set_last_error(int code);
int			get_last_error(void);

#endif // ENVIRONMENT_H