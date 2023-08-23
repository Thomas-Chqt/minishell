/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btr_get_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:58:14 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/05 14:25:51 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

t_btree	*btr_get_last(t_btree *tree, t_btr_trvsl traversal)
{
	t_btree	*current;

	if (tree == NULL || traversal == postorder)
		return (tree);
	current = tree;
	while (current->right != NULL)
		current = current->right;
	return (current);
}
