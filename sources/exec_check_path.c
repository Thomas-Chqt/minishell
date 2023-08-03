/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_check_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:08:29 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/02 18:53:07 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_cmdpath(char *cmd_path, int flag)
{
	int			err;
	struct stat	buf;

	errno = 0;
	if (flag == ACCESS_FOK)
	{
		err = access(cmd_path, F_OK);
		if (err == 0)
			return (0);
	}
	else if (flag == ACCESS_XOK)
	{
		err = access(cmd_path, X_OK);
		if (err == -1)
			cmd_cant_use(cmd_path, CMD_SIMPLE);
		else
			return (0);
	}
	return (1);
}
