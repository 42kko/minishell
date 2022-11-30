# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_pipe
{
	int	cnt;
	int	*p;
}	t_pipe;

int main()
{
	struct s_pipe	pip;

	pip.p = (int *)malloc(sizeof(int) * pip.cnt * 2);
	pipe(pip.p);
	pipe(pip.p + 2);
	printf("%d\n",pip.p[0]);
	printf("%d\n",pip.p[2]);
	return 0;
}