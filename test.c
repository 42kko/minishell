#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int	is_wild(char *wild_str, char *file_name);
int is_wildSub(char *wild_str, char *file_name, int index);


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}

char	*ft_strdup(char *s)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(*s) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*sub;

	i = 0;
	if (!s || start < 0)
		return (NULL);
	s_len = ft_strlen(s);
	if ((size_t)start >= s_len)
		return (ft_strdup(""));
	if (s_len - (size_t)start - 1 > len)
		sub = (char *)malloc(sizeof(char) * (len + 1));
	else
		sub = (char *)malloc(sizeof(char) * (s_len - start + 1));
	if (!sub)
		return (NULL);
	while (s[i] && i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}

int	is_wild(char *wild_str, char *file_name)
{
	int	wild_len;
	int	file_len;
	int	i;

	wild_len = ft_strlen(wild_str);
	file_len = ft_strlen(file_name);
	i = 0;
	while (i < wild_len && i < file_len && wild_str[i] == file_name[i])
		i++;
	if (i == wild_len && i == file_len)
		return 1;
	else if (i == wild_len && i != file_len)
		return 0;
	if (wild_str[i] == '*')
	{
		if (is_wildSub(wild_str, file_name, i))
			return 1;
	}
	return 0;
}

int is_wildSub(char *wild_str, char *file_name, int index)
{
	int	i;
	int	file_len;

	file_len = ft_strlen(file_name);
	i = 0;
	while (index + i <= file_len)
	{
		if (is_wild(ft_substr(wild_str, index + 1, ft_strlen(wild_str)), ft_substr(file_name, index + i, file_len)))
		{
			return 1;
		}
		i++;
	}
	return 0;
}

// int	cnt_pwd(t_token *tok, char *wild_str)
// {
//    struct dirent   *file;
//    DIR            *dir_ptr;
//    char         *tmp;
//    int            i;

//    i = 0;
//    tmp = getcwd(0, 4096);
//    dir_ptr = opendir_util(tmp, tok);
//    if (dir_ptr == 0)
//       return (-1);
//    file = readdir(dir_ptr);
//    while (file != NULL)
//    {
//       if (file->d_name[0] != '.') // 숨겨진 폴더는 제외하고 카운트
//          i++;
//       file = readdir(dir_ptr);
//    }
//    closedir(dir_ptr);
//    return (i);
// }

int main()
{
	int res = is_wild("m*i*n", "main");
	printf("%d\n", res);
}