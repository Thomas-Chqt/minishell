/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_last_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:40:39 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/28 15:35:02 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int	*get_last_error_ptr(void);
char		**get_default_home_ptr(void);

void	set_last_error(int code)
{
	*(get_last_error_ptr()) = code;
}

int	get_last_error(void)
{
	return (*(get_last_error_ptr()));
}

char	*get_default_home(void)
{
	return (*get_default_home_ptr());
}

char	**get_default_home_ptr(void)
{
	static char	*default_home = NULL;

	return (&default_home);
}

static int	*get_last_error_ptr(void)
{
	static int	last_error = 0;

	return (&last_error);
}
