/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_last_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:40:39 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/18 17:04:25 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int	*get_last_error_ptr(void);

void	set_last_error(int code)
{
	*(get_last_error_ptr()) = code;
}

int	get_last_error(void)
{
	return (*(get_last_error_ptr()));
}

static int	*get_last_error_ptr(void)
{
	static int	last_error = 0;

	return (&last_error);
}
