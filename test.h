#ifndef TEST_H
# define TEST_H

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
# include <string.h>

#define TCMD 1
#define TOUT 2 //>
#define TADDOUT 4 //>>
#define TIN 8 //<
#define TDOC 16 //<<
#define TPIPE 251 //|
#define TOR 254 //||
#define TAND 255 //&&



//
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	**ft_split(const char *s, char c);
int	ft_isprint(int c);



//
#endif