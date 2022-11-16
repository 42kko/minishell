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

typedef enum e_oper_type	t_oper_type;

enum e_oper_type
{
	NO_TYPE,
	TCMD,
	TOUT, //>
	TADDOUT, //>>
	TIN, //<
	TDOC, //<<
	TPIPE, //|
	TOR, //||
	TAND, //&
	TDAND, //&&
	TSEMI, //;
};

typedef struct s_token
{
	t_oper_type			type;
	char				**cmd;
	char				*line;
	struct s_token		*next;
}	t_token;

//
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	**ft_split(const char *s, char c);
int	ft_isprint(int c);
t_token	*ft_lstlast(t_token *lst);
char	*ft_strdup(const char *s);
int		get_sec_arr_len(char **arr);




#endif