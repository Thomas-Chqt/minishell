/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:38:58 by hotph             #+#    #+#             */
/*   Updated: 2023/08/20 18:25:52 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

static int	check_arg(char *str, int argc)
{
	int	status;

	status = 0;
	if (str != NULL && str_isdigit(str) == -1)
		status = printf_error_msg
			("minishell: exit: %: numeric argument required", &str, 2);
	else if (argc > 2)
		status = print_error_msg("minishell: exit: too many arguments", 1);
	return (status);
}

static void	exit_parent(int status, t_ast *ast, t_dexec *dexec)
{
	clear_env();
	clean_ast(ast);
	free(dexec->cmd_path);
	free(dexec->cmd_opts);
	if (status != -1)
		exit(status);
	exit (get_last_error());
}

static int	exit_do_nonfork_or_child(t_dexec *dexec, t_ast *node)
{
	int	status;

	status = check_arg(dexec->cmd_opts[1], get_argc(node));
	if (dexec->flag_pipe == 0)
	{
		if (status == 0 && dexec->cmd_opts[1] == NULL)
			exit_parent (-1, node, dexec);
		else if (status == 0)
			exit_parent ((t_uint8)ft_atoi(dexec->cmd_opts[1]), node, dexec);
		else if (status == 2)
			exit_parent (2, node, dexec);
		return (-1);
	}
	else
	{
		if (status == 0 && dexec->cmd_opts[1] == NULL)
			exit (get_last_error()); 
		else if (status == 0)
			exit ((t_uint8)ft_atoi(dexec->cmd_opts[1]));
		else if (status == 2)
			exit (2);
		exit (1);
	}
	return (0);
}

int	built_in_exit(t_dexec *dexec, t_ast *node)
{
	int		pid;

	pid = 0;
	if (dexec->flag_pipe == 1)
		pid = fork();
	if (pid == 0)
		return (exit_do_nonfork_or_child(dexec, node));
	else
		return (pid);
}
