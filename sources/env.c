/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:45:34 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/05 15:00:18 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void print_val(void *data)
{
	char **str_ptr;

	str_ptr = (char **)data;
	ft_printf("%s\n", *str_ptr);
}

int	env(void)
{
	t_list	*val_list;

	val_list = dic_to_val_lstmap(*(env_get_dict()));
	if (val_list != NULL)
	{
		ft_lstiter(val_list, &print_val);
		ft_lstclear(&val_list, &free_str_ptr);
		return (0);
	}
	return (1);
}
