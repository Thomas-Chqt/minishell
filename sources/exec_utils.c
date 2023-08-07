/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:35:15 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/07 21:59:29 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	argv_fill_option(char **argv, t_ast *node);

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
	if (node->data->data[ft_strlen(node->data->data) - 1] == '/')
		return (NULL);
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

	if (node->data->data[ft_strlen(node->data->data) - 1] == '/')
		return (NULL);
	argv = ft_calloc(get_argc(node) + 1, sizeof(char *));
	if (argv == NULL)
		return (NULL);
	if (ft_strchr(node->data->data, '/') == NULL)
		argv[0] = node->data->data;
	else
		argv[0] = ft_strrchr(node->data->data, '/') + 1;
	if (argv_fill_option(argv, node->right) != 0)
		free_null((void **)&argv);
	return (argv);
}

static int	argv_fill_option(char **argv, t_ast *node)
{
	t_uint64	i;
	t_ast		*current;

	i = 1;
	current = node;
	while (current != NULL)
	{
		argv[i] = current->data->data;
		if (argv[i] == NULL)
			return (1);
		current = current->right;
		i++;
	}
	return (0);
}
