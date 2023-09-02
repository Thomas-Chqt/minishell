/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:56:27 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/02 13:17:06 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	get_pwd_wrap(char **dest)
{
	int	status;

	*dest = get_env("PWD", &status);
	if (status == MALLOC_ERROR)
		return (print_error(MALLOC_ERROR));
	else if (*dest == NULL || (*dest != NULL && *dest[0] == '\0'))
	{
		if (*dest != NULL)
			free(*dest);
		*dest = getcwd(NULL, 0);
		if (*dest == NULL)
			return (perror_wrap("cd: getcwd", 1));
	}
	return (status);
}

void	curtail_str_by_char(char *str, char delim)
{
	if (ft_strrchr(str, delim) == NULL)
		str[0] = '\0';
	else if (ft_strrchr(str, delim) == str)
		str[1] = '\0';
	else
		*(ft_strrchr(str, delim)) = '\0';
}
