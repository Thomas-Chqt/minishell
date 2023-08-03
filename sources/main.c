/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:27 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/03 16:48:03 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int main(int ac, char **av, char **envp)
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

void	print_token(void *data)
{
	t_token	*token;

	token = (t_token *)data;
	ft_printf("(");
	if (token->type == DLESS)
		ft_printf("DLESS");
	else if (token->type == DGREAT)
		ft_printf("DGREAT");
	else if (token->type == LESS)
		ft_printf("LESS");
	else if (token->type == GREAT)
		ft_printf("GREAT");
	else if (token->type == PIPE)
		ft_printf("PIPE");
	else
		ft_printf("%s", token->data);
	ft_printf(") -> ");
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*cmd;
	t_toklist	*toklist = NULL;
	t_toklist	*toklist_bacup;
	int			error;
	char		error_msg[100];
	t_ast		*tree;

	if (init_env(envp) != 0)
		return (1);
	while (1)
	{
		cmd = readline("minishell > ");
		if (cmd == NULL)
			continue ;
		if (cmd[0] == '\0')
		{
			free(cmd);
			continue ;
		}
		add_history(cmd);
		if (ft_strncmp(cmd, "exit", 4) == 0)
		{
			free(cmd);
			break ;
		}
		error = fill_toklist(cmd, &toklist);
		free(cmd);
		if (error == 0)
		{
			toklist_bacup = toklist;
			if (chek_full_cmd(&toklist, error_msg) == 0)
			{
				toklist = toklist_bacup;
				tree = make_ast(toklist);
				if (tree != NULL)
				{
					btr_iter((t_btree *)tree, preorder, &print_token);
					ft_printf("\n");
					btr_clear((t_btree *)tree, NULL);
				}
			}
			else
			{
				ft_printf("%s\n", error_msg);
				toklist = toklist_bacup;
			}
		}
		if (error == 1)
		{
			ft_printf("quote error\n");
		}
		if (error == 2)
		{
			ft_printf("Malloc error\n");
		}
		ft_lstclear((t_list **)&toklist, &free_token);
	}
	clean_env();
	return (0);
}