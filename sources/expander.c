/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:31:43 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/12 23:09:19 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	expand_string(char **str_ptr);
static int	substitute_toklist(t_exp_toklst *tok_lst);
static int	substitute_token(t_exp_token *token);
static char	*join_lst(t_exp_toklst *list);

int	expand_ast(t_ast *ast)
{
	if (ast == NULL)
		return (0);
	if (ast->data != NULL && ast->data->type == TEXT)
	{
		if (expand_string(&ast->data->data) != 0)
			return (1);
	}
	if (expand_ast(ast->right) != 0)
		return (1);
	if (expand_ast(ast->left) != 0)
		return (1);
	return (0);
}

static int	expand_string(char **str_ptr)
{
	t_exp_toklst	*token_list;
	int				return_val;

	token_list = make_exp_toklst(*str_ptr);
	if (token_list == NULL)
		return (MALLOC_ERROR);
	return_val = substitute_toklist(token_list);
	if (return_val == 0)
	{
		free(*str_ptr);
		*str_ptr = join_lst(token_list);
		ft_lstclear((t_list **)&token_list, &free_exp_toklst);
		if (*str_ptr == NULL)
			return (MALLOC_ERROR);
		return (0);
	}
	ft_lstclear((t_list **)&token_list, &free_exp_toklst);
	return (return_val);
}

static int	substitute_toklist(t_exp_toklst *tok_lst)
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
		return (printf_error_msg("minishell: %: bad substitution\n", &watched->data->str, 1));
	return (0);
}

static int	substitute_token(t_exp_token *token)
{
	char	*founded;

	if (token->type == substit)
	{
		if (is_all_valid_env(token->str) == false)
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
		return (expand_string(&token->str));
	return (0);
}

static char	*join_lst(t_exp_toklst *list)
{
	t_uint64		str_len;
	char			*str;
	t_exp_toklst	*watched;

	str_len = 0;
	watched = list;
	while (watched != NULL)
	{
		str_len += ft_strlen(watched->data->str);
		watched = watched->next;
	}
	str = malloc(sizeof(char) * (str_len + 1));
	if (str == NULL)
		return (NULL);
	watched = list;
	while (watched != NULL)
	{
		ft_strlcat(str, watched->data->str, str_len + 1);
		watched = watched->next;
	}
	return (str);
}
