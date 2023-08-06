/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:41 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/06 14:34:58 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include "external_functions.h"
# include "error_codes.h"

# ifdef MEMCHECK
#  include <memory_leak_detector.h>
# endif // MEMCHECK

# define ERROR_MSG_MAX_LEN 100

typedef struct s_toklist	t_toklist;
typedef struct s_ast		t_ast;

int			init_env(char *envp[]);
int			set_env(const char *key, const char *val, t_bool exported);
char		*get_env(const char *key);
int			export_env(const char *key);
void		clean_env(void);

t_toklist	*make_toklist(const char *cmd, char *error_msg);
void		clean_toklist(t_toklist **token_list);

t_ast		*make_ast(t_toklist *toklist);

int			env(int argc, char *argv[]);
int			export(int argc, char *argv[]);

/*----Debug----*/

void		print_token(void *data);
void		print_env_var(void *data);

#endif // MINISHELL_H