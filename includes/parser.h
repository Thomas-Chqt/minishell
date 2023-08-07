/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:01:56 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/06 21:00:54 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef struct s_ast		t_ast;

struct s_ast
{
	t_token	*data;
	t_ast	*parent;
	t_ast	*left;
	t_ast	*right;
};

int		add_cmd_back(t_token *token, t_ast *tree);
int		add_io(t_toklist **token_lst, t_ast *tree);
int		add_io_back(t_toklist **token_lst, t_ast *tree);
int		add_io_front(t_toklist **token_lst, t_ast *tree);
int		add_separator(t_token *token, t_ast **tree);

t_ast	*make_ast(t_toklist *toklist);
t_bool	is_io_token(t_token *token);

#endif // PARSER_H