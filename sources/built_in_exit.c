/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:38:58 by hotph             #+#    #+#             */
/*   Updated: 2023/08/18 16:54:49 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	str_isdigit(char *str)
{
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

static void	exit_parent(int status, t_ast *ast, t_dexec *dexec)//Draft. Discuss with @Thomas.
{
	if (status != -1)
		set_last_error(status);
	clean_env();
	clean_ast(ast);
	free(dexec->cmd_path);
	free(dexec->cmd_opts);
	exit (status);//can I exit here? with nothing change $? .
}

static int	exit_do_nonfork_or_child(t_dexec *dexec, t_ast *node)
{
	int	status;

	status = check_arg(dexec->cmd_opts[1], get_argc(node));
	if (dexec->flag_pipe == 0)
	{
		//------after exit_parent fixes, this part should be changed.------
		// if (status == 0 && dexec->cmd_opts[1] == NULL)
		// 	exit_parent (-1);//set $? & free all allocated memory
		// else if (status == 0)
		// 	exit_parent ((t_uint8)ft_atoi(dexec->cmd_opts[1]));//set $? & free all allocated memory
		// else if (status == 2)
		// 	exit_parent (2);//set $? & free all allocated memory
		// else
			return (-1);
	}
	else
	{
		if (status == 0 && dexec->cmd_opts[1] == NULL)
			exit (0);//actually, it should not set $?. Can we control set $?, if exit val is minus? 
		else if (status == 0)
			exit ((t_uint8)ft_atoi(dexec->cmd_opts[1]));
		else if (status == 2)
			exit (2);
		else
			exit (1);
	}
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
