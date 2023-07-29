/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:27 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/29 17:32:12 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef MEMCHECK

__attribute__((destructor))
static void	destructor(void)
{
	char	*pid;
	char	*cmd;

	print_report();
	pid = ft_itoa(getpid());
	cmd = ft_strjoin("leaks -q ", pid);
	system((const char *)cmd);
	free(pid);
	free(cmd);
}

#endif // MEMCHECK

// int	main(int argc, char *argv[], char *envp[])
// {
// 	char	*cmd;
// 	char	*var;
// 	char	*splited_str[2];

// 	if (init_env(envp) != 0)
// 		return (1);

// 	cmd = NULL;
// 	while (1)
// 	{
// 		cmd = readline("minishell > ");
// 		if (ft_strncmp(cmd, "exit", 4) == 0)
// 			break ;
// 		if (ft_strchr(cmd, '=') == NULL)
// 		{
// 			var = get_env((const char *)cmd);
// 			ft_printf("%s\n", var);
// 			free(var);
// 			free(cmd);
// 			continue ;
// 		}
// 		splited_str[0] = ft_substr(cmd, 0, ft_strchr(cmd, '=') - cmd);
// 		splited_str[1] = ft_strdup(ft_strchr(cmd, '=') + 1);	
// 		if (splited_str[0] == NULL || splited_str[1] == NULL || set_env(splited_str[0], splited_str[1]) != 0)
// 		{
// 			free(splited_str[0]);
// 			free(splited_str[1]);
// 			break ;
// 		}
// 		free(splited_str[0]);
// 		free(splited_str[1]);
// 		free(cmd);
// 	}
// 	free(cmd);
// 	clean_env();
// 	return (0);
// }

void	print_token(void *data)
{
	t_token	*token;

	token = (t_token *)data;
	ft_printf("(");
	if (token->type == DLESS)
		ft_printf("DLESS");
	if (token->type == DGREAT)
		ft_printf("DGREAT");
	if (token->type == LESS)
		ft_printf("LESS");
	if (token->type == GREAT)
		ft_printf("GREAT");
	if (token->type == PIPE)
		ft_printf("PIPE");
	ft_printf("%s) -> ", token->data);
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*cmd;
	char		*var;
	char		*splited_str[2];
	t_toklist	*toklist;

	if (init_env(envp) != 0)
		return (1);

	cmd = NULL;
	while (1)
	{
		cmd = readline("minishell > ");
		if (ft_strncmp(cmd, "exit", 4) == 0)
		{
			free(cmd);
			break ;
		}
		toklist = make_toklist(cmd);
		if (toklist == NULL)
			ft_printf("Parse Error");
		ft_lstiter((t_list *)toklist, &print_token);

	}

	clean_env();
	return (0);
}
