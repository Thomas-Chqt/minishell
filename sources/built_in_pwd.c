/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hotph <hotph@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:52:27 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/30 12:37:06 by hotph            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	built_in_pwd(void)
{
	char	*cwd;

	cwd = get_env("PWD", NULL);
	if (cwd == NULL)
		return (perror_wrap("cd: ", 1));
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
