#include "test.h"

char	*ft_strdup(const char *s)
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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
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
	size_t			i;
	unsigned char	a;

	a = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == a)
			return ((char *)(s + i));
		i++;
	}
	if (!c)
		return ((char *)(s + i));
	return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	front;
	size_t	back;

	if (!s1 || !set)
		return (0);
	front = 0;
	back = ft_strlen(s1);
	while (s1[front] && ft_strchr(set, s1[front]))
		front++;
	while (s1[back - 1] && ft_strchr(set, s1[back - 1]) && back > front)
		back--;
	str = (char *)malloc(sizeof(char) * (back - front + 1));
	if (!str)
		return (NULL);
	else
		ft_strlcpy(str, &s1[front], back - front + 1);
	return (str);
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


static char	**ft_malloc_arr(char *s, char c)
{
	size_t	cnt;
	char	**arr;

	cnt = 0;
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			cnt++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	arr = (char **)malloc(sizeof(char *) * (cnt + 1));
	return (arr);
}

static char	*strdup_split(char const *s, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

static void	*free_all(char **str, size_t l)
{
	size_t	i;

	i = 0;
	while (str[i] && i <= l)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static size_t	strlen_split(char const *s, char c)
{
	size_t		len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		len;
	char		**arr;

	i = 0;
	len = 0;
	arr = ft_malloc_arr((char *)s, c);
	if (!arr)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = strlen_split(s, c);
			arr[i] = strdup_split(s, len);
			s += len;
			len = 0;
			if (!arr[i++])
				return (free_all(arr, i));
		}
		else
			s++;
	}
	arr[i] = 0;
	return (arr);
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
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

