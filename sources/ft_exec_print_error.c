/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_print_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:50:34 by sotanaka          #+#    #+#             */
/*   Updated: 2023/08/01 18:46:34 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_mes_error(char *message)
{
	ft_putstr_fd (message, 2);
	return (EXIT_FAILURE);
}

int	ft_print_perror(char *original_message)
{
	perror(original_message);
	return (EXIT_FAILURE);
}
