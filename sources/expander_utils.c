/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:38:06 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/20 18:57:27 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	add_next_str_2(char *str, t_uint64 *i, t_str_list **list,
				t_bool dquoted);

t_bool	is_end_nomal_token(char c)
{
	return (
		c == '\''
		|| c == '\"'
		|| c == '$'
		|| c == '\0'
	);
}

int	add_next_str(char *str, t_uint64 *i, t_str_list **list, t_bool dquoted)
{
	int	temp_ret;

	if (!dquoted)
	{
		temp_ret = exp_lstadd_tilde(str, i, list);
		if (temp_ret != PARSING_ERROR)
			return (temp_ret);
		temp_ret = exp_lstadd_quote(str, i, list);
		if (temp_ret != PARSING_ERROR)
			return (temp_ret);
		temp_ret = exp_lstadd_dquote(str, i, list);
		if (temp_ret != PARSING_ERROR)
			return (temp_ret);
	}
	temp_ret = exp_lstadd_bracket(str, i, list, !dquoted);
	if (temp_ret != PARSING_ERROR)
		return (temp_ret);
	return (add_next_str_2(str, i, list, dquoted));
}

static int	add_next_str_2(char *str, t_uint64 *i, t_str_list **list,
				t_bool dquoted)
{
	int	temp_ret;

	temp_ret = exp_lstadd_no_bracket(str, i, list);
	if (temp_ret != PARSING_ERROR)
		return (temp_ret);
	temp_ret = exp_lstadd_last_error(str, i, list);
	if (temp_ret != PARSING_ERROR)
		return (temp_ret);
	return (exp_lstadd_normal(str, i, list));
}
