/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sipmle_tokens_pt2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 21:29:14 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/30 21:29:42 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	chek_pipe(t_toklist **toklist_head, char *error_msg)
{
	if (((*toklist_head) == NULL || (*toklist_head)->data->type != PIPE)
		&& error_msg == NULL)
		return (1);
	if ((*toklist_head) == NULL)
		return (ft_strlcpy(error_msg, "Missing token", 100));
	if ((*toklist_head)->data->type == DLESS
		|| (*toklist_head)->data->type == LESS)
		return (ft_strlcpy(error_msg, "Unexpected token \'<\'", 100));
	if ((*toklist_head)->data->type == DGREAT
		|| (*toklist_head)->data->type == GREAT)
		return (ft_strlcpy(error_msg, "Unexpected token \'>\'", 100));
	if ((*toklist_head)->data->type == TEXT)
	{
		ft_strlcpy(error_msg, "Unexpected token : \'", 100);
		ft_strlcat(error_msg, (*toklist_head)->data->data, 100);
		return (ft_strlcat(error_msg, "\'", 100));
	}
	(*toklist_head) = (*toklist_head)->next;
	return (0);
}

int	chek_text(t_toklist **toklist_head, char *error_msg)
{
	if (((*toklist_head) == NULL || (*toklist_head)->data->type != TEXT)
		&& error_msg == NULL)
		return (1);
	if ((*toklist_head) == NULL)
		return (ft_strlcpy(error_msg, "Missing token", 100));
	if ((*toklist_head)->data->type == DLESS
		|| (*toklist_head)->data->type == LESS)
		return (ft_strlcpy(error_msg, "Unexpected token \'<\'", 100));
	if ((*toklist_head)->data->type == DGREAT
		|| (*toklist_head)->data->type == GREAT)
		return (ft_strlcpy(error_msg, "Unexpected token \'>\'", 100));
	if ((*toklist_head)->data->type == PIPE)
		return (ft_strlcpy(error_msg, "Unexpected token \'|\'", 100));
	(*toklist_head) = (*toklist_head)->next;
	return (0);
}
