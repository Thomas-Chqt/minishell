/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:20:36 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/24 14:58:32 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_INTERNAL_H
# define LIBFT_INTERNAL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>
# include <stdarg.h>

# ifdef MEMCHECK
#  include <memory_leak_detector.h>
# endif // MEMCHECK

# include "libft.h"

#endif // LIBFT_INTERNAL_H