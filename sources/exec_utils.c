/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:35:15 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/07 18:42:27 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//! No way to know if there is no path or if the allocation failed
char	*get_cmd_path(t_ast *node)
{
	if (node->data->type != TEXT || node->data->data == NULL)
		return (NULL);
	if (ft_strchr(node->data->data, '/') == NULL)
		return (NULL);
	return (
		ft_substr(node->data->data, 0,
			ft_strrchr(node->data->data, '/') + 1 - node->data->data)
	);
}

char	*get_cmd_prog(t_ast *node)
{
	if (node->data->type != TEXT || node->data->data == NULL)
		return (NULL);
	if (ft_strchr(node->data->data, '/') == NULL)
		return (ft_strdup(node->data->data));
	return (ft_strdup(ft_strrchr(node->data->data, '/') + 1));
}

int	get_argc(t_ast *node)
{
	if (node->data->type != TEXT)
		return (0);
	return (btr_size((t_btree *)node->right) + 1);
}

char	**get_argv(t_ast *node)
{
	char		**argv;
	t_uint64	i;
	t_ast		*current;

	argv = ft_calloc(get_argc(node), sizeof(char *));
	if (argv == NULL)
		return (NULL);
	current = node;
	i = 0;
	while (current != NULL)
	{
		argv[i] = ft_strdup(current->data->data);
		if (argv[i] == NULL)
		{
			free_splited_str(argv);
			return (NULL);
		}
		current = current->right;
		i++;
	}
	return (argv);
}
