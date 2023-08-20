/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:29:07 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/20 17:02:53 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include "error.h"
# include "lexer.h"
# include "parser.h"
# include "environment.h"

typedef struct s_str_list	t_str_list;

struct s_str_list
{
	char		*str;
	t_str_list	*next;
};

int		expand_ast(t_ast *ast);

int		exp_lstadd_quote(char *str, t_uint64 *i, t_str_list **list);
int		exp_lstadd_dquote(char *str, t_uint64 *i, t_str_list **list);
int		exp_lstadd_bracket(char *str, t_uint64 *i, t_str_list **list,
			t_bool print);
int		exp_lstadd_no_bracket(char *str, t_uint64 *i, t_str_list **list);
int		exp_lstadd_last_error(char *str, t_uint64 *i, t_str_list **list);
int		exp_lstadd_tilde(char *str, t_uint64 *i, t_str_list **list);
int		exp_lstadd_normal(char *str, t_uint64 *i, t_str_list **list);

t_bool	is_end_nomal_token(char c);
int		add_next_str(char *str, t_uint64 *i, t_str_list **list, t_bool dquoted);

int		add_substitued(char *str, size_t len, t_str_list **list);

#endif // EXPANDER_H