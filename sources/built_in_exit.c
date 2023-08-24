/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:38:58 by hotph             #+#    #+#             */
/*   Updated: 2023/08/24 20:26:04 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parser.h"

static int	str_isdigit(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (-1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		str++;
	}
	return (0);
}

static int	check_arg(char *str, int argc, int flag_pipe)
{
	int	status;

	status = 0;
	if (str != NULL && str_isdigit(str) == -1)
	{
		if (flag_pipe == 0)
			ft_putstr_fd("exit\n", 1);
		status = printf_error_msg
			("minishell: exit: %: numeric argument required", &str, 2);
	}
	else if (argc > 2)
		status = print_error_msg("minishell: exit: too many arguments", 1);
	return (status);
}

static void	exit_parent(int status, t_ast *ast, t_exe *exe)
{
	clear_env();
	clean_ast(ast);
	free(exe->cmd_path);
	free(exe->cmd_opts);
	if (status != -1)
		exit(status);
	exit (get_last_error());
}

int	built_in_exit(t_exe *exe, t_ast *node)
{
	int	status;

	status = check_arg(exe->cmd_opts[1], get_argc(node), exe->flag_pipe);
	if (exe->flag_pipe == 0)
	{
		if (status == 0 && exe->cmd_opts[1] == NULL)
			exit_parent (-1, node, exe);
		else if (status == 0)
			exit_parent ((t_uint8)ft_atoi(exe->cmd_opts[1]), node, exe);
		else if (status == 2)
			exit_parent (2, node, exe);
		return (-1);
	}
	else
	{
		if (status == 0 && exe->cmd_opts[1] == NULL)
			exit (get_last_error());
		else if (status == 0)
			exit ((t_uint8)ft_atoi(exe->cmd_opts[1]));
		else if (status == 2)
			exit (2);
		exit (1);
	}
	return (0);
}
