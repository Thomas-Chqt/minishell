/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:51:42 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/12 20:10:18 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "error.h"

typedef enum e_token_type	t_token_type;
typedef struct s_token		t_token;
typedef struct s_toklist	t_toklist;

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

int			toklist_text_new(const char *cmd, t_uint64 *i, t_toklist **list);
int			toklist_pipe_new(const char *cmd, t_uint64 *i, t_toklist **list);
int			toklist_io_new(const char *cmd, t_uint64 *i, t_toklist **list);
void		free_token(void *token);

int			recurse_full_cmd(const char *cmd, t_uint64 *i, t_toklist **list);
int			recurse_simple_cmd(const char *cmd, t_uint64 *i, t_toklist **list);
int			recurse_io_list(const char *cmd, t_uint64 *i, t_toklist **list);
int			recurse_io_file(const char *cmd, t_uint64 *i, t_toklist **list);
int			recurse_text_list(const char *cmd, t_uint64 *i, t_toklist **list);

t_toklist	*make_toklist(const char *cmd);
void		clean_toklist(t_toklist **token_list);

#endif // LEXER_H