/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:05:59 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/26 17:24:30 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include "error.h"

# include "lexer.h"

typedef t_token		t_pre_token;
typedef t_toklist	t_pre_toklist;

int	expand_toklist(t_toklist **token_list);
int	put_expanded_file_fd(int fd_in, size_t len, int fd_out);

#endif // EXPANDER_H