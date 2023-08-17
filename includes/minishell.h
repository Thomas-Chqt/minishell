/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:41 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/17 18:53:16 by tchoquet         ###   ########.fr       */
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

void		minishell_loop(void);

t_ast		*parse_cmd(const char *cmd);
int			expand_ast(t_ast *ast);
int			execute_ast(t_ast *ast);
void		clean_ast(t_ast *ast);

int			env(int argc, char *argv[]);
int			export(int argc, char *argv[]);

#endif // MINISHELL_H