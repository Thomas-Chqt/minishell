/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:41 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/07 16:50:04 by hotph            ###   ########.fr       */
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

typedef struct s_toklist	t_toklist;
typedef struct s_ast		t_ast;

int			init_env(char *envp[]);
void		clean_env(void);

t_ast		*parse_cmd(const char *cmd);
void		execute_ast(t_ast *ast);
void		clean_ast(t_ast *ast);

void		minishell_loop(void);

int			env(int argc, char *argv[]);
int			export(int argc, char *argv[]);

#endif // MINISHELL_H