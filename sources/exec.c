/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:58:32 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/07 21:42:51 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// TODO : execution start here
void	execute_ast(t_ast *ast)
{
	char	*path;
	char	*prog;
	char	**argv;
	int		i;

	path = get_cmd_path(ast);
	ft_printf("path : %s\n", path);
	free(path);
	prog = get_cmd_prog(ast);
	ft_printf("prog : %s\n", prog);
	free(prog);
	ft_printf("argc : %d\n", get_argc(ast));
	argv = get_argv(ast);
	if (argv == NULL)
		ft_printf("argv : NULL\n");
	else
	{
		i = 0;
		while (i < get_argc(ast))
		{
			ft_printf("argv[%d] : %s\n", i, argv[i]);
			i++;
		}
		ft_printf("argv[%d] : %s\n", i, argv[i]);
		free(argv);
	}
}
