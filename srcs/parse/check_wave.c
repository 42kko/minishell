/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wave.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:45:49 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/09 00:08:28 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strdup_section(char *s, int left, int right)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (right - left + 1));
	if (!str)
		throw_error(MALLOC_ERR);
	while (s[left] && left < right)
		str[i++] = s[left++];
	str[i] = '\0';
	return (str);
}

static int	if_only_wave(t_token **token, char **arr, int *right)
{
	char	*line;

	line = (*token)->line;
	if (ft_strncmp(*arr, "~", 2) == 0)
	{
		free(*arr);
		*arr = ft_strdup(ft_getenv((*token)->info->env_list, "~"));
		if (!(*arr))
			throw_error(MALLOC_ERR);
		while (line[(*right)] == ' ')
				(*right)++;
		return (ONLY_WAVE);
	}
	return (FAIL);
}

t_wave_type	check_is_wave(t_token **token, char **arr, int *left, int *right)
{
	char	*line;

	line = (*token)->line;
	push_index_until_space_or_oper(line, right);
	*arr = ft_strdup_section(line, *left, *right);
	if (if_only_wave(token, arr, right))
		return (ONLY_WAVE);
	*right = *left;
	while (line[(*right)] == '<' || line[(*right)] == '>')
		(*right)++;
	while (line[(*right)] && line[(*right)] == ' ')
		(*right)++;
	if (ft_strncmp(line + *right, "~", 1) == 0)
	{
		free(*arr);
		*right = *left;
		return (MAYBE_HOME);
	}
	free(*arr);
	*right = *left;
	return (NO_WAVE);
}

void	change_wave_to_home(t_token **token, char **arr, int i)
{
	char	*wave;
	char	*front_part;
	char	*back_part;
	char	*new;
	char	*tmp;

	wave = ft_getenv((*token)->info->env_list, "~");
	front_part = ft_substr(*arr, 0, i);
	back_part = ft_strdup(*arr + i + 1);
	new = ft_strjoin(front_part, wave);
	if (!new)
		throw_error(MALLOC_ERR);
	tmp = new;
	new = ft_strjoin(new, back_part);
	if (!new)
		throw_error(MALLOC_ERR);
	free(tmp);
	free(wave);
	free(front_part);
	free(back_part);
	free(*arr);
	*arr = new;
}
