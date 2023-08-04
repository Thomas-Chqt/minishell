/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD:sources/test.c
/*   test.c                                             :+:      :+:    :+:   */
=======
/*   error_codes.h                                      :+:      :+:    :+:   */
>>>>>>> origin/thomas-dev:includes/error_codes.h
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:sources/test.c
/*   Created: 2023/07/23 22:45:40 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/02 18:04:26 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

// int main()
// {
// 	char	*pwd;

// 	pwd = getcwd(NULL, 0);
// 	printf("%s\n", pwd);
// 	open("aaaa", O_RDONLY);
// 	perror("open");
// }
=======
/*   Created: 2023/08/03 15:30:04 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/03 18:41:02 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CODES_H
# define ERROR_CODES_H

# define MALLOC_ERROR 1111
# define MISSING_QUOTE 2222

#endif // ERROR_CODES_H
>>>>>>> origin/thomas-dev:includes/error_codes.h
