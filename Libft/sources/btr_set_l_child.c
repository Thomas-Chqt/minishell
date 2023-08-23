/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btr_set_l_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:46:18 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/02 17:28:36 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

int	btr_set_l_child(t_btree *node, t_btree *left)
{
	if (node == NULL)
		return (1);
	node->left = left;
	if (left == NULL)
		return (2);
	left->parent = node;
	return (0);
}
