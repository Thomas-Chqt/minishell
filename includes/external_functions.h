/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_functions.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:54:17 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/29 14:50:30 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNAL_FUNCTIONS_H
# define EXTERNAL_FUNCTIONS_H

# include <sys/errno.h>

# ifdef MEMCHECK

int		getpid(void);
int		system(const char *command);

# endif // MEMCHECK

char	*readline(const char *prompt);

// rl_clear_history
// rl_on_new_line,
// rl_replace_line
// rl_redisplay
// add_history,
// printf

void	*malloc(size_t size);
void	free(void *ptr);

// write
// access
// open
// read,
// close
// fork
// wait
// waitpid
// wait3
// wait4
// signal,
// sigaction
// sigemptyset
// sigaddset
// kill
// exit,
// getcwd
// chdir
// stat
// lstat
// fstat
// unlink

int		execve(const char *path, char *const argv[], char *const envp[]);

// dup
// dup2
// pipe
// opendir
// readdir
// closedir,
// strerror
// perror
// isatty
// ttyname
// ttyslot
// ioctl,

char	*getenv(const char *name);

// tcsetattr
// tcgetattr
// tgetent
// tgetflag,
// tgetnum
// tgetstr
// tgoto
// tputs

#endif // EXTERNAL_FUNCTIONS_H