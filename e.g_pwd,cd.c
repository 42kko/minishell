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
# include <fcntl.h>

void	ft_pwd(void)
{
	char	*s;
	s = getcwd(0, 0);
	printf("%s\n", s);
}

int main()
{
	ft_pwd();
	pid_t pid = fork();
	if (pid == 0)
	{
		chdir("..");
		exit(1);
	}
	ft_pwd();
}
