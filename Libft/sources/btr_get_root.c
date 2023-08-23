/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btr_get_root.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:08:25 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/05 14:25:59 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

t_btree	*btr_get_root(t_btree *node)
{
	t_btree	*current;

	if (node == NULL)
		return (NULL);
	current = node;
	while (current->parent != NULL)
		current = current->parent;
	return (current);
}
