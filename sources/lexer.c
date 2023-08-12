/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:12:11 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/12 19:55:56 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_toklist	*make_toklist(const char *cmd)
{
	t_toklist	*new_lst;
	t_uint64	i;
	int			error_code;

	i = 0;
	new_lst = NULL;
	error_code = recurse_full_cmd(cmd, &i, &new_lst);
	if (error_code == 0)
		return (new_lst);
	print_error(error_code);
	return (NULL);
}

void	clean_toklist(t_toklist **token_list)
{
	ft_lstclear((t_list **)token_list, &free_token);
}
