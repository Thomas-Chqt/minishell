/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:29:07 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/12 23:28:14 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"
# include "env.h"

typedef struct s_exp_token		t_exp_token;
typedef enum e_tok_type			t_tok_type;
typedef struct s_exp_toklist	t_exp_toklst;

enum e_tok_type 
{
	normal,
	substit,
	dquote
};

struct s_exp_token
{
	char		*str;
	t_tok_type	type;
};

struct s_exp_toklist
{
	t_exp_token		*data;
	t_exp_toklst	*next;
};

t_exp_toklst	*make_exp_toklst(char *str);
void			free_exp_toklst(t_exp_toklst **lst);
t_exp_toklst	*exp_toklst_new(char *str, t_uint64 len, t_tok_type type);


int				exp_add_env(char *str, t_uint64 *i, t_exp_toklst **list);
int				exp_add_dquote(char *str, t_uint64 *i, t_exp_toklst **list);
int				exp_add_quote(char *str, t_uint64 *i, t_exp_toklst **list);
int				exp_add_normal(char *str, t_uint64 *i, t_exp_toklst **list);

int				exp_add_last_err(char *str, t_uint64 *i, t_exp_toklst **list);
int				exp_add_env_brake(char *str, t_uint64 *i, t_exp_toklst **list);
int				exp_add_env_no_brake(char *str, t_uint64 *i, t_exp_toklst **list);

#endif // EXPANDER_H