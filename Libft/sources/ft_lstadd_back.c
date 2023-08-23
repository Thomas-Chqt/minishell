/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:25:31 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/30 12:17:55 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	**watched;

	if (lst == NULL || new == NULL)
		return ;
	watched = lst;
	while (*watched != NULL)
		watched = &((*watched)->next);
	*watched = new;
}
