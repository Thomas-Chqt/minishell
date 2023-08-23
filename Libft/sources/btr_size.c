/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btr_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:28:40 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/07 18:29:54 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

size_t	btr_size(t_btree *tree)
{
	if (tree == NULL)
		return (0);
	return (btr_size(tree->left) + btr_size(tree->right) + 1);
}
