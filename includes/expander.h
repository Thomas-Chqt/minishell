/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:29:07 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/18 22:21:36 by tchoquet         ###   ########.fr       */
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

int	expand_ast(t_ast *ast);

#endif // EXPANDER_H