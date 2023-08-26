/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:05:59 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/26 00:05:21 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include "error.h"

#include "tokenizer.h"

t_toklist *make_expanded_toklist(t_token token, int *error);

int add_expanded_next(char *str, t_uint64 *i, t_toklist **list, t_bool dquoted);

int add_substitued_last_error(char *str, t_uint64 *i, t_toklist **list);
int	add_substitued_tilde(char *str, t_uint64 *i, t_toklist **list);
int add_expanded_quote(char *str, t_uint64 *i, t_toklist **list);
int add_expanded_dquote(char *str, t_uint64 *i, t_toklist **list);
int add_expanded_dollar(char *str, t_uint64 *i, t_toklist **list);
int	add_expanded_normal(char *str, t_uint64 *i, t_toklist **list);

int add_substitued_arg(char *str, t_uint64 *i, t_toklist **list);
int add_substitued_brace(char *str, t_uint64 *i, t_toklist **list);
int add_substitued_no_brace(char *str, t_uint64 *i, t_toklist **list);
int add_substitued(char *str, size_t len, t_toklist **list);

int join_dquoted_toklist(t_toklist **token_list);

t_toklist *retoken(t_token token);
int	add_retoken(t_toklist *retoken, t_toklist **token_list);

char **str_splitwhitespace(char *str);

#endif // EXPANDER_H