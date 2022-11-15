#include "test.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s != (char)c)
	{
		if (*s == 0)
			return (0);
		s++;
	}
	return ((char *)s);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	i;
	size_t	j;
	size_t	size;

	if (!s1)
		return (0);
	i = 0;
	j = ft_strlen(s1);
	size = j;
	while (s1[i] && ft_strchr(set, s1[i]) && size > i)
		i++;
	while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && j > i)
		j--;
	ret = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!ret)
		return (0);
	ft_memcpy(ret, s1 + i, j - i);
	ret[j - i] = 0;
	return (ret);
}

static void	ft_putchar(const char *s, size_t i, size_t j, char *ret)
{
	size_t	a;

	a = 0;
	while (a < j)
	{
		ret[a] = s[i + a];
		a++;
	}
	ret[a] = 0;
}

static int	ft_input(const char *s, char c, char **ret, int *val)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i + j] != c && s[i + j])
			j++;
		if (j != 0)
			ret[*val] = (char *)malloc(sizeof(char) * j + 1);
		if (!ret[*val] && j != 0)
		{
			(*val)--;
			return (0);
		}
		if (j != 0)
			ft_putchar (s, i, j, ret[*val]);
		(*val)++;
		i = i + j;
	}
	return (1);
}

static size_t	wordc(const char *s, char c)
{
	size_t	size;
	size_t	i;
	size_t	ret;

	size = ft_strlen(s);
	i = 0;
	ret = 0;
	while (s[i])
	{
		if ((s[i] != c && i == 0) || (s[i] != c && s[i - 1] == c))
			ret++;
		i++;
	}
	if (i == 0)
		return (0);
	return (ret);
}

static void	memfree(char **ret, int val)
{
	while (val >= 0)
	{
		free(ret[val]);
		val--;
	}
	free(ret);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	int		result;
	int		val;
	size_t	word;

	if (!s)
		return (0);
	word = wordc(s, c);
	ret = (char **)malloc(sizeof(char *) * (word + 1));
	if (!ret)
		return (0);
	ret[word] = 0;
	val = 0;
	result = ft_input(s, c, ret, &val);
	if (result == 0)
	{
		memfree(ret, val);
		return (0);
	}
	return (ret);
}

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (0);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}
