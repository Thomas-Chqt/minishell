/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analizer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:59:56 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/30 21:37:44 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chek_dless(t_toklist **toklist_head, char *error_msg);
int	chek_dgreat(t_toklist **toklist_head, char *error_msg);
int	chek_less(t_toklist **toklist_head, char *error_msg);
int	chek_great(t_toklist **toklist_head, char *error_msg);
int	chek_pipe(t_toklist **toklist_head, char *error_msg);
int	chek_text(t_toklist **toklist_head, char *error_msg);
int	chek_simple_cmd(t_toklist **toklist_head, char *error_msg);
int	chek_io_list(t_toklist **toklist_head, char *error_msg);
int	chek_io_file(t_toklist **toklist_head, char *error_msg);
int	chek_token_list(t_toklist **toklist_head, char *error_msg);

int	chek_full_cmd(t_toklist **toklist_head, char *error_msg)
{
	t_toklist	*start_node;

	start_node = *toklist_head;
	if (chek_simple_cmd(toklist_head, error_msg) == 0
		&& chek_pipe(toklist_head, error_msg) == 0
		&& chek_full_cmd(toklist_head, error_msg) == 0)
		return (0);
	*toklist_head = start_node;
	if (chek_simple_cmd(toklist_head, error_msg) == 0
		&& (*toklist_head) == NULL)
		return (0);
	return (1);
}

int	chek_simple_cmd(t_toklist **toklist_head, char *error_msg)
{
	t_toklist	*start_node;

	start_node = *toklist_head;
	if (chek_io_list(toklist_head, error_msg) == 0
		&& chek_token_list(toklist_head, error_msg) == 0)
		return (0);
	*toklist_head = start_node;
	if (chek_token_list(toklist_head, error_msg) == 0
		&& chek_io_list(toklist_head, error_msg) == 0)
		return (0);
	*toklist_head = start_node;
	if (chek_token_list(toklist_head, error_msg) == 0)
		return (0);
	return (1);
}

int	chek_io_list(t_toklist **toklist_head, char *error_msg)
{
	t_toklist	*start_node;

	start_node = *toklist_head;
	if (chek_io_file(toklist_head, error_msg) == 0
		&& chek_io_list(toklist_head, error_msg) == 0)
		return (0);
	*toklist_head = start_node;
	if (chek_io_file(toklist_head, error_msg) == 0)
		return (0);
	return (1);
}

int	chek_io_file(t_toklist **toklist_head, char *error_msg)
{
	t_toklist	*start_node;

	start_node = *toklist_head;
	if (chek_less(toklist_head, error_msg) == 0
		&& chek_text(toklist_head, error_msg) == 0)
		return (0);
	*toklist_head = start_node;
	if (chek_great(toklist_head, error_msg) == 0
		&& chek_text(toklist_head, error_msg) == 0)
		return (0);
	*toklist_head = start_node;
	if (chek_dless(toklist_head, error_msg) == 0
		&& chek_text(toklist_head, error_msg) == 0)
		return (0);
	*toklist_head = start_node;
	if (chek_dgreat(toklist_head, error_msg) == 0
		&& chek_text(toklist_head, error_msg) == 0)
		return (0);
	return (1);
}

int	chek_token_list(t_toklist **toklist_head, char *error_msg)
{
	t_toklist	*start_node;

	start_node = *toklist_head;
	if (chek_text(toklist_head, error_msg) == 0
		&& chek_token_list(toklist_head, error_msg) == 0)
		return (0);
	*toklist_head = start_node;
	if (chek_text(toklist_head, error_msg) == 0)
		return (0);
	return (1);
}
