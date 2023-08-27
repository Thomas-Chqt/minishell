/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:51:42 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/27 13:15:22 by tchoquet         ###   ########.fr       */
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

t_toklist	*toklist_new(t_token_type type, char *data);
t_toklist	*make_toklist(const char *cmd);
void		free_token(void *token);

#endif // LEXER_H