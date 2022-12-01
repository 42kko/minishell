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

int main()
{
	int	i;
	struct stat *buf;
	i = stat("/bin/ls", buf);
	printf("i:%d\n",i);
	
	return 0;
}