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

void    ft_sep(char **line)
{
    while (*line)
    {
        if (**line == 'e')
        {
            printf("sep\n");
            break;
        }
        (*line)++;
    }
}

void    ft_sep1(char **line)
{
    int i = 0;
    char *tmp = *line;
    while (*tmp)
    {
        if (*tmp == 'l')
        {
            printf("sep1\n");
            break;
        }
        tmp++;
    }
    printf("line : %s\n", *line);
    i = 3;
    printf("line : %c\n", (*line)[i]);
    while ((*line)[i])
    {
        if ((*line)[i] == 'l')
        {
            printf("sep2\n");
            break;
        }
        i++;
        printf("what\n");
    }
    while ((*line))
    {
        if ((**line) == 'l')
        {
            printf("sep5\n");
            break;
        }
        (*line)++;
        printf("what\n");
    }
}

void    ft_sep2(char *line)
{
    while (*line)
    {
        if (*line == '<')
        {
            printf("hi\n");
            break;
        }
        line++;
    }
}

void    ft_hi(char *line)
{
    printf("*: %s\n", line);
    while (*line)
    {
        if (*line == 'b')
        {
            printf("jho\n");
            break;
        }
        line++;
    }
    return;
}

void    ft_sep3(char **line)
{
    printf("**: %s\n", *line);
    while (**line)
    {
        if (**line == '<')
        {
            printf("jdfho\n");
            ft_hi(*line);
            break;
        }
        line++;
    }
}

void    ft_sep4(char **line)
{
    while (**line)
    {
        (*line)++;
    }
}

int main()
{
    char *line = "<e ls -al -al <<b <<c <<a l>Q >D >V >BA >D";

    // ft_sep(&line);
    // printf("s:%s\n", line);
    // ft_sep1(&line);
    // printf("s1:%s\n", line);
    // ft_sep2(line);
    // ft_sep3(&line);
    // ft_sep4(&line);
    while (*line)
        ft_sep4(&line);
    printf("s1:%s\n", line);
}