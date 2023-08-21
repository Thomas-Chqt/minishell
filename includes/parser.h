/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:01:56 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/21 11:38:46 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "error.h"

# include "lexer.h"

typedef struct s_ast		t_ast;

struct s_ast
{
	t_token	*data;
	t_ast	*parent;
	t_ast	*left;
	t_ast	*right;
};

t_ast	*make_ast(t_toklist *toklist);
void	clean_ast(t_ast *ast);

#endif // PARSER_H