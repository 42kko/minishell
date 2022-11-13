/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_for_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:30:01 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/13 02:04:23 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

void	create_str_to_c(char const *s, char **arr, size_t *i, char c)
{
	size_t		len;

	len = strlen_split(s, c);
	arr[*i] = strdup_split(s, len);
	s += len;
	len = 0;
	if (!arr[*i++])
		return (free_all(arr, i));
}

char	**ft_split_for_env(char const *s)
{
	size_t		i;
	char		**arr;

	i = 0;
	arr = (char **)malloc(sizeof(char *) * 3);
	if (!arr)
		return (0);
	create_str_to_c(s, arr, &i, '=');
	create_str_to_c(s, arr, &i, '=');
	arr[i] = 0;
	return (arr);
}
