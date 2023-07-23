/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_functions.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:54:17 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/23 23:25:37 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNAL_FUNCTIONS_H
# define EXTERNAL_FUNCTIONS_H

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
// malloc
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
// execve,
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
// getenv
// tcsetattr
// tcgetattr
// tgetent
// tgetflag,
// tgetnum
// tgetstr
// tgoto
// tputs

#endif // EXTERNAL_FUNCTIONS_H