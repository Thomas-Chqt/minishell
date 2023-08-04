/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 22:22:34 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/03 22:22:51 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	is_io_token(t_token *token)
{
	return (
		token->type == DLESS
		|| token->type == DGREAT
		|| token->type == LESS
		|| token->type == GREAT
	);
}
