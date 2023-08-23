/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btr_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:53:01 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/02 17:30:32 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

t_btree	*btr_new(void *data)
{
	t_btree	*new_node;

	new_node = malloc(sizeof(t_btree));
	if (new_node == NULL)
		return (NULL);
	new_node->parent = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->data = data;
	return (new_node);
}
