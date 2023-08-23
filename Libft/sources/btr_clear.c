/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btr_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:59:41 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/02 19:30:22 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

void	btr_clear(t_btree *tree, void (*del)(void *))
{
	if (tree == NULL)
		return ;
	btr_clear(tree->left, del);
	btr_clear(tree->right, del);
	if (del != NULL)
		del(tree->data);
	if (tree->parent != NULL)
	{
		if (tree->parent->right != NULL && tree->parent->right == tree)
			tree->parent->right = NULL;
		else if (tree->parent->left != NULL && tree->parent->left == tree)
			tree->parent->left = NULL;
	}
	free(tree);
}
