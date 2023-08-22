/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:12:11 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/22 17:27:04 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "environment.h"

int			recurse_full_cmd(const char *cmd, t_uint64 *i, t_toklist **list);
static int	exec_first_node(t_toklist **new_lst);

t_toklist	*make_toklist(const char *cmd)
{
	t_toklist	*new_lst;
	t_uint64	i;
	int			error_code;

	i = 0;
	new_lst = NULL;
	error_code = recurse_full_cmd(cmd, &i, &new_lst);
	if (error_code == 0)
	{
		error_code = exec_first_node(&new_lst);
		if (error_code != 0)
		{
			clean_toklist(&new_lst);
			set_last_error(print_error(error_code));
		}
		return (new_lst);
	}
	set_last_error(print_error(error_code));
	return (NULL);
}

void	clean_toklist(t_toklist **token_list)
{
	ft_lstclear((t_list **)token_list, &free_token);
}

static int	exec_first_node(t_toklist **new_lst)
{
	t_toklist	*first_node;
	int			temp_ret;

	if ((*new_lst)->data->data == NULL || (*new_lst)->next != NULL)
		return (0);
	if (is_valid_keyval((*new_lst)->data->data) == false)
		return (0);
	first_node = (t_toklist *)lst_rmvfrst((t_list **)new_lst);
	temp_ret = set_env_single_str(first_node->data->data, false);
	clean_toklist(&first_node);
	return (temp_ret);
}
