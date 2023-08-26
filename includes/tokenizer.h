/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:44:14 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/26 16:54:01 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"
# include "error.h"

typedef enum e_token_type	t_token_type;
typedef struct s_token		t_token;
typedef struct s_toklist	t_toklist;

enum e_token_type
{
	DLESS = 1,
	DGREAT = 2,
	LESS = 3,
	GREAT = 4,
	PIPE = 5,
	TEXT = 6,
	QUOTED = 7,
	DQUOTED = 8
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

t_toklist	*make_toklist(const char *cmd);
void		free_token(void *token);

int			add_text_token(const char *cmd, t_uint64 *i, t_toklist **list);
int			add_pipe_token(const char *cmd, t_uint64 *i, t_toklist **list);
int			add_io_token(const char *cmd, t_uint64 *i, t_toklist **list);

t_toklist	*toklist_new(t_token_type type, char *data);
int			set_text_token_len(const char *cmd, size_t *len);

#endif // TOKENIZER_H