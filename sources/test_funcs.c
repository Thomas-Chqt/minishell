/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:40:03 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/05 14:18:29 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_token(void *data)
{
	t_token	*token;

	token = (t_token *)data;
	ft_printf("(");
	if (token->type == DLESS)
		ft_printf("DLESS");
	else if (token->type == DGREAT)
		ft_printf("DGREAT");
	else if (token->type == LESS)
		ft_printf("LESS");
	else if (token->type == GREAT)
		ft_printf("GREAT");
	else if (token->type == PIPE)
		ft_printf("PIPE");
	else
		ft_printf("%s", token->data);
	ft_printf(") -> ");
}

void	print_env_var(void *data)
{
	t_token	*token;
	char	*str;

	token = (t_token *)data;
	if (token->type != TEXT)
		return ;
	str = get_env((const char *)token->data);
	ft_printf("%s\n", str);
	free(str);
}
