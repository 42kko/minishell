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

int	ft_access(const char *pathname, int mode)
{
	struct stat buf;
	int	r;
	int	w;
	int	x;

	r = 0;
	w = 0;
	x = 0;
	if(stat(pathname, &buf) < 0)
		return (-1);
	if ((buf.st_mode & S_IRUSR) != 0)
		r = 4;
	if ((buf.st_mode & S_IWUSR) != 0)
		w = 2;
	if ((buf.st_mode & S_IXUSR) != 0)
		x = 1;
	if (r == mode || w == mode || x == mode || r + w == mode || r + x == mode \
	|| w + x == mode || r + w + x == mode || mode == 0)
		return (0);
	return (-1);
}

int main(int argc, char *argv[])
{
	struct stat buf;
	char tmp[100] = "./hi";

	if (stat(tmp, &buf) == -1)
	{
		printf("stat err\n");
		return 1;
	}
	printf("st_mode  : %o(octal), %x(hex)\n", buf.st_mode, buf.st_mode);
	printf("regular file : %o(octal), %x(hex)\n", buf.st_mode & S_IRWXU, buf.st_mode & S_IRWXU);
	printf("regular file : %o(octal), %x(hex)\n", buf.st_mode & (S_IRWXU >> 3), buf.st_mode & (S_IRWXU >> 3));
	printf("regular file : %o(octal), %x(hex)\n", buf.st_mode & (S_IRWXU >> 6), buf.st_mode & (S_IRWXU >> 6));

	printf("a:%d, f:%d\n", access("/bin/ls", 1), ft_access("/bin/ls", 1));
	return 0;
}