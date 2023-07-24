/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:27 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/24 02:45:41 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef MEMCHECK

__attribute__((destructor))
static void	destructor(void)
{
	char	*pid;
	char	*cmd;

	// print_reporjt();
	pid = ft_itoa(getpid());
	cmd = ft_strjoin("leaks -q ", pid);
	// system((const char *)cmd);
	free(pid);
	free(cmd);
}

#endif // MEMCHECK

int	main(int argc, char *argv[], char *envp[])
{
	char *env[] = {"PATH=Bite", NULL};
	execve("print_env", NULL, env);
	return (errno);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	for (size_t i = 0; envp[i] != NULL; i++)
// 		ft_printf("%s\n", envp[i]);
// 	ft_printf("\n\n%s\n", getenv("PATH"));

// 	return (0);
// }