/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:41 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/17 16:12:43 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include "external_functions.h"

# ifdef MEMCHECK
#  include <memory_leak_detector.h>
# endif // MEMCHECK

typedef struct s_toklist	t_toklist;
typedef struct s_ast		t_ast;

int			init_env(char *envp[]);
void		clean_env(void);
int			set_last_error(int code);
int			get_last_error(void);

void		minishell_loop(void);

t_ast		*parse_cmd(const char *cmd);
int			expand_ast(t_ast *ast);
int			execute_ast(t_ast *ast);
void		clean_ast(t_ast *ast);

int			env(int argc, char *argv[]);
int			export(int argc, char *argv[]);

#endif // MINISHELL_H