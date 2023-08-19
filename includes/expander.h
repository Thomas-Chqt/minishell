/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:29:07 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/19 18:32:27 by tchoquet         ###   ########.fr       */
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

int		exp_lstadd_normal(char *str, t_uint64 *i, t_str_list **list);
int		exp_lstadd_bracket(char *str, t_uint64 *i, t_str_list **list);

t_bool	is_end_nomal_token(char c);

int		add_substitued(char *str, size_t len, t_str_list **list);

#endif // EXPANDER_H