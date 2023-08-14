/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_substitution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:33:28 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/14 14:09:41 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	substitute_toklist(t_exp_toklst *tok_lst)
{
	t_exp_toklst	*watched;
	char			*founded;
	int				temp_ret;

	watched = tok_lst;
	while (watched != NULL)
	{
		temp_ret = substitute_token(watched->data);
		if (temp_ret == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (temp_ret == BAD_SUBSTITUTION)
			break ;
		watched = watched->next;
	}
	if (watched != NULL && watched->data->type == substit)
		return (printf_error_msg("minishell: ${%}: bad substitution",
				&watched->data->str, BAD_SUBSTITUTION));
	else if (watched != NULL && watched->data->type == dquote)
		return (printf_error_msg("minishell: %: bad substitution",
				&watched->data->str, BAD_SUBSTITUTION));
	return (0);
}

int	substitute_toklist_no_print(t_exp_toklst *tok_lst)
{
	t_exp_toklst	*watched;
	char			*founded;
	int				temp_ret;

	watched = tok_lst;
	while (watched != NULL)
	{
		temp_ret = substitute_token(watched->data);
		if (temp_ret == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (temp_ret == BAD_SUBSTITUTION)
			break ;
		watched = watched->next;
	}
	if (watched != NULL)
		return (BAD_SUBSTITUTION);
	return (0);
}

int	substitute_token(t_exp_token *token)
{
	char	*founded;

	if (token->type == substit)
	{
		if (token->str[0] != '?'
			&& (is_all_valid_env(token->str) == false || token->str[0] == '\0'))
			return (BAD_SUBSTITUTION);
		founded = get_env(token->str);
		if (founded == NULL)
			founded = ft_strdup("");
		if (founded == NULL)
			return (MALLOC_ERROR);
		free(token->str);
		token->str = founded;
	}
	if (token->type == dquote)
		return (expand_dquote_string(&token->str));
	return (0);
}
