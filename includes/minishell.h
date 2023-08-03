/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:41 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/03 16:47:06 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include "external_functions.h"

# ifdef MEMCHECK
#  include <memory_leak_detector.h>
# endif // MEMCHECK

typedef enum e_token_type	t_token_type;
typedef struct s_token		t_token;
typedef struct s_toklist	t_toklist;
typedef struct s_ast		t_ast;

enum e_token_type
{
	DLESS,
	DGREAT,
	LESS,
	GREAT,
	PIPE,
	TEXT
};

struct s_token
{
	t_token_type	type;
	char			*data;
};

struct s_toklist
{
	t_token		*data;
	t_toklist	*next;
};

struct s_ast
{
	t_token	*data;
	t_ast	*parent;
	t_ast	*left;
	t_ast	*right;
};

int			init_env(char *envp[]);
int			set_env(const char *key, const char *val);
char		*get_env(const char *key);
void		clean_env(void);

t_toklist	*toklist_new(t_token_type type, char *data);
void		free_token(void *token);

int			fill_toklist(char *command, t_toklist **toklist_head);

int			chek_full_cmd(t_toklist **toklist_head, char *error_msg);

t_ast		*make_ast(t_toklist *toklist);

#endif // MINISHELL_H