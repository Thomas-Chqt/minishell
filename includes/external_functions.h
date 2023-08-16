/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_functions.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotanaka <sotanaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:54:17 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/16 14:12:38 by sotanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNAL_FUNCTIONS_H
# define EXTERNAL_FUNCTIONS_H

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define STDIN_FILENO 0
# define STDOUT_FILENO 1
# define STDERR_FILENO 2

# define F_OK 0
# define X_OK 1
# define W_OK 2
# define R_OK 4

# include <errno.h>
# include <stddef.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

# ifdef MEMCHECK

int		getpid(void);
int		system(const char *command);

# endif // MEMCHECK

typedef int	t_pid;

char	*readline(const char *prompt);

// rl_clear_history
// rl_on_new_line,
// rl_replace_line
// rl_redisplay

int		add_history(const char *str);

// printf

void	*malloc(size_t size);
void	free(void *ptr);

// write

int		access(const char *path, int permision);

// int		open(const char *pathname, int flags);
// read,

int		close(int fildes);
t_pid	fork(void);

// wait

pid_t	waitpid(pid_t pid, int *stat_loc, int options);

// wait3
// wait4
// signal,
// sigaction
// sigemptyset
// sigaddset
// kill

void	exit(int status);
char	*getcwd(char *buf, size_t size);

int		chdir(const char *path);

int		stat(const char *path, struct stat *buf);

// lstat
// fstat
// unlink

int		execve(const char *path, char *const argv[], char *const envp[]);

// dup

int		dup2(int fildes, int fildes2);
int		pipe(int pipefd[2]);

// opendir
// readdir
// closedir,
char	*strerror(int errnum);

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