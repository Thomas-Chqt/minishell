/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btr_set_r_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:57:39 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/02 17:28:42 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

int	btr_set_r_child(t_btree *node, t_btree *right)
{
	if (node == NULL)
		return (1);
	node->right = right;
	if (right == NULL)
		return (2);
	right->parent = node;
	return (0);
}
