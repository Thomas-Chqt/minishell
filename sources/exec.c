/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:58:32 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/07 17:01:53 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// TODO : execution start here
void	execute_ast(t_ast *ast)
{
	scan_btree_pipe(0, 1, ast);
}
