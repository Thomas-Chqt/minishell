/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:24:15 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/02 20:46:41 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_syntree	*make_syntree(t_toklist *toklist)
{
	t_toklist	*tokl_cur;
	t_syntree	*text_branch;
	t_syntree	*io_branch;

	tokl_cur = toklist;
	while (tokl_cur != NULL)
	{
		if (tokl_cur->data->type == TEXT);
	}
	
}