/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:45:40 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/01 15:37:17 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
	char	pwd[255];

	getcwd(pwd, 255);
	printf("%s\n", pwd);
	open("aaaa", O_RDONLY);
	perror("open");
}