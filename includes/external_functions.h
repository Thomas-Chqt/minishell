/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_functions.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:54:17 by tchoquet          #+#    #+#             */
/*   Updated: 2023/07/31 19:24:58 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNAL_FUNCTIONS_H
# define EXTERNAL_FUNCTIONS_H

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define CMD_SIMPLE 2
# define CMD_NOTFOUND 3

#define F_OK 0     
#define X_OK (1<<0)
#define W_OK (1<<1)
#define R_OK (1<<2)

# include <errno.h>
# include <stddef.h>

# ifdef MEMCHECK

int		getpid(void);
int		system(const char *command);

# endif // MEMCHECK

typedef int t_pid;

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

int		access(const char *path, int permision);

// open
// read,
// close
t_pid	fork(void);
// wait
// waitpid
// wait3
// wait4
// signal,
// sigaction
// sigemptyset
// sigaddset
// kill
void	exit(int status);
char	*getcwd(char *buf, size_t size);
// chdir
// stat
// lstat
// fstat
// unlink

int		execve(const char *path, char *const argv[], char *const envp[]);

// dup
// dup2
int		pipe(int pipefd[2]);
// opendir
// readdir
// closedir,
// strerror
void	perror(const char *s);
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