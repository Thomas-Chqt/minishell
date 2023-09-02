/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 11:56:27 by sotanaka          #+#    #+#             */
/*   Updated: 2023/09/02 12:02:40 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	get_env_wrap(char *key, char **dest)
{
	*dest = get_env(key, NULL);
	if (*dest == NULL)
		return (print_error(MALLOC_ERROR));
	return (0);
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
