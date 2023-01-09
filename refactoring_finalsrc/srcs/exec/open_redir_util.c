/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:25:21 by jihonkim          #+#    #+#             */
/*   Updated: 2023/01/03 14:25:54 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_index_redir(char *tmp, int i)
{
	while (tmp[i] != 0 && tmp[i] != ' ')
	{
		if (ft_is_comma(tmp[i]))
			push_index_com(tmp, &i);
		i++;
	}
	return (i);
}

char	*get_prev_line(t_token *tok, t_token *first, int idx)
{
	char	*tmp;
	char	*ret;
	int		i;

	(void)tok;
	tmp = first->parent->right->line;
	i = 0;
	while (tmp[i] && idx != 0)
	{
		if (ft_is_redir(tmp[i]))
		{
			i++;
			if (ft_is_redir(tmp[i]))
				i++;
			idx--;
		}
		i++;
	}
	while (ft_is_redir(tmp[i]) == NO_DIREC)
		i++;
	ret = ft_substr(tmp, i, get_index_redir(tmp, i));
	return (ret);
}

int	com_wild_redir(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (ft_is_comma(tmp[i]))
		{
			push_index_com(tmp, &i);
		}
		else if (tmp[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_redir(char *s)
{
	if (ft_is_redir(*s))
		s++;
	if (ft_is_redir(*s))
		s++;
	while (*s == ' ')
		s++;
	return (s);
}

void	change_lien(t_token *tok, char **tmp1)
{
	char	*tmp;

	tmp = tok->line;
	tok->line = ft_strdup(tmp1[0]);
	free(tmp);
	tmp = tok->line;
	if (tok->type == TDOC)
		tok->line = ft_strjoin("<<", tok->line);
	if (tok->type == TIN)
		tok->line = ft_strjoin("<", tok->line);
	if (tok->type == TOUT)
		tok->line = ft_strjoin(">", tok->line);
	if (tok->type == TADDOUT)
		tok->line = ft_strjoin(">>", tok->line);
	free(tmp);
}
