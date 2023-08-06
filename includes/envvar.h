/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:26:37 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/05 20:11:40 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVVAR_H
# define ENVVAR_H

# include "minishell.h"

typedef struct s_env_entry	t_env_entry;

struct s_env_entry
{
	char	*key;
	char	*value;
	t_bool	is_export;
};

t_env_entry	*env_entry_new(const char *key, const char *val);
void		del_env_entry(void *v_entry);
t_bool		is_env_key_equal(void *entry, void *key);

t_list		**get_lstenv(void);

#endif // ENVVAR_H