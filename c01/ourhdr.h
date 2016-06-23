/* Our own header, to be included *after* all standard system headers */

#ifndef __ourhdr_h
#define __ourhdr_h

#include <sys/types.h>	/* required for some of our prototypes */
#include <stdio.h>	/* for convenience */
#include <stdlib.h>	/* for convenience */
#include <string.h>	/* for convenience */
#include <unistd.h>	/* for convenience */
#include <errno.h>	/* for definition of errno */
#include <stdarg.h>	/* ANSI C header file */

#define MAXLINE 4096  /* max line length */
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
		/* default file access permissions for new files */
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
		/* default permissions for new directories */

typedef void Sigfunc(int);  /* for signal handlers */
			/* 4.3BSD Reno <signal.h> doesn't define SIG_ERR */
#if defined(SIG_IGN) && !defined(SIG_ERR)
#define SIG_ERR ((Sigfunc *)-1)
#endif

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

			/* prototypes for our own functions */
char	*path_alloc(int *);		/* Program 2.2 */
int	open_max(void);			/* Program 2.3 */
void	clr_fl(int, int);		/* Program 3.5 */
void	set_fl(int, int);		/* Program 3.5 */
void	pr_exit(int);			/* Program 8.3 */
void	pr_mask(const char *);		/* Program 10.10 */
Sigfunc *signal_intr(int, Sigfunc *);	/* Program 10.13 */

int	tty_cbreak(int);		/* Program 11.10 */
int	tty_raw(int);			/* Program 11.10 */
int	tty_reset(int);			/* Program 11.10 */
void	tty_atexit(void);		/* Program 11.10 */
#ifdef ECHO  /* only if <termios.h> has been included */
struct termios *tty_termios(void);	/* Program 11.10 */
#endif

void	sleep_us(unsigned int);		/* Exercise 12.6 */
ssize_t readn(int, void *, size_t);	/* Program 12.13 */
ssize_t writen(int, const void *, size_t);  /* Program 12.12 */
int	daemon_init(void);		/* Program 13.1 */

int	s_pipe(int *);			/* Program 15.2 and 15.3 */
int	recv_fd(int, ssize_t (*func)(int, const void *, size_t));
					/* Program 15.6 and 15.8 */
int	send_fd(int, int);		/* Program 15.5 and 15.7 */
int	send_err(int, int, const char *);  /* Program 15.4 */
int	serv_listen(const char *);	/* Program 15.19 and 15.22 */
int	serv_accept(int, uid_t *);	/* Program 15.20 and 15.24 */
int	cli_conn(const char *);		/* Program 15.21 and 15.23 */
int	buf_args(char *, int (*func)(int, char **));
					/* Program 15.17 */
int	ptym_open(char *);		/* Program 19.1 and 19.2 */
int	ptys_open(int, char *);		/* Program 19.1 and 19.2 */
#ifdef TIOCGWINSZ
pid_t	pty_fork(int *, char *, const struct termios *, const struct winsize *);
					/* Program 19.3 */
#endif

int	lock_reg(int, int, int, off_t, int, off_t);
					/* Program 12.2 */
#define	read_lock(fd, offset, whence, len) \
	lock_reg(fd, F_SETLK, F_RDLCK, offset, whence, len)
#define	readw_lock(fd, offset, whence, len) \
	lock_reg(fd, F_SETLKW, F_RDLCK, offset, whence, len)
#define	write_lock(fd, offset, whence, len) \
	lock_reg(fd, F_SETLK, F_WRLCK, offset, whence, len)
#define	writew_lock(fd, offset, whence, len) \
	lock_reg(fd, F_SETLKW, F_WRLCK, offset, whence, len)
#define un_lock(fd, offset, whence, len) \
	lock_reg(fd, F_SETLK, F_UNLCK, offset, whence, len)

pid_t	lock_test(int, int, off_t, int, off_t);
					/* Program 12.3 */
#define	is_readlock(fd, offset, whence, len) \
	lock_test(fd, F_RDLCK, offset, whence, len)
#define is_writelock(fd, offset, whence, len) \
	lock_test(fd, F_WRLCK, offset, whence, len)

void	err_dump(const char *, ...);	/* Appendix B */
void	err_msg(const char *, ...);
void	err_quit(const char *, ...);
void	err_ret(const char *, ...);
void	err_sys(const char *, ...);

void	log_msg(const char *, ...);	/* Appendix B */
void	log_open(const char *, int, int);
void	log_quit(const char *, ...);
void	log_ret(const char *, ...);
void	log_sys(const char *, ...);

void	TELL_WAIT(void);		/* parent/child from Section 8.8 */
void	TELL_PARENT(pid_t);
void	TELL_CHILD(pid_t);
void	WAIT_PARENT(void);
void	WAIT_CHILD(void);

static void err_doit(int, const char *, va_list);
char	*pname = NULL;	/* caller can set this from argv[0] */

/* Nonfatal error related to a system call.
 * Print a message and return. */

void err_ret(const char *fmt, ...)
{
	va_list	ap;
	va_start(ap, fmt);
	err_doit(1, fmt, ap);
	va_end(ap);
	return;
}

/* Fatal error related to a system call.
 * Print a message and terminate. */

void err_sys(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, fmt, ap);
	va_end(ap);
	exit(1);
}

/* Fatal error related to a system call.
 * Print a message, dump core, and terminate. */

void err_dump(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, fmt, ap);
	va_end(ap);
	abort();	/* dump core and terminate */
	exit(1);	/* shouldn't get here */
}

/* Nofatal error unrelated to a system call.
 * Print a message and return. */

void err_msg(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(0, fmt, ap);
	va_end(ap);
	return;
}

/* fatal error unrelated to a system call.
 * Print a message and terminate. */

void err_quit(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(0, fmt, ap);
	va_end(ap);
	exit(1);
}

/* Print a message and return to caller.
 * Caller specifies "errnoflag". */

static void err_doit(int errnoflag, const char *fmt, va_list ap)
{
	int errno_save;
	char buf[MAXLINE];

	errno_save = errno;	/* value caller might want printed */
	vsprintf(buf, fmt, ap);
	if (errnoflag)
		sprintf(buf+strlen(buf), ": %s", strerror(errno_save));
	strcat(buf, "\n");
	fflush(stdout);		/* in case stdout and stderr are the same */
	fputs(buf, stderr);
	fflush(NULL);		/* flushes all stdio output streams */
	return;
}

#endif /* __ourhdr_h */
