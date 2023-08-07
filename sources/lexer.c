/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:12:11 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/06 21:42:25 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_toklist	*make_toklist(const char *cmd, char *error_msg)
{
	t_toklist	*new_lst;
	t_uint64	i;
	int			error_code;

	i = 0;
	new_lst = NULL;
	error_code = recurse_full_cmd(cmd, &i, &new_lst);
	if (error_code == 0)
		return (new_lst);
	if (error_code == MALLOC_ERROR)
		ft_strlcpy(error_msg, "Malloc errror", ERROR_MSG_MAX_LEN);
	else if (error_code == MISSING_QUOTE + '\'')
		ft_strlcpy(error_msg, "Missing quote `\'`", ERROR_MSG_MAX_LEN);
	else if (error_code == MISSING_QUOTE + '\"')
		ft_strlcpy(error_msg, "Missing quote `\"`", ERROR_MSG_MAX_LEN);
	else if (error_code == 1)
		ft_strlcpy(error_msg, "Parsing error", ERROR_MSG_MAX_LEN);
	else
		ft_strlcpy(error_msg, "Unknown error", ERROR_MSG_MAX_LEN);
	return (NULL);
}

void	clean_toklist(t_toklist **token_list)
{
	ft_lstclear((t_list **)token_list, &free_token);
}
