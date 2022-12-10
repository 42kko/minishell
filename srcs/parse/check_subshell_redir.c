/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_subshell_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 01:43:47 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/10 14:46:14 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_token(t_token *tok, char *tmp)
{
	t_token	*new;
	int		i;

	i = 0;
	new = new_token(tok->info);
	i = cnt_redir(tmp, &tok);
	push_index(tmp + i, &i);
	new->line = ft_substr(tmp, 0, i + 1);
	if (tok->prev)
	{
		tok->prev->next = new;
		new->prev = tok->prev;
	}
	tok->prev = new;
	new->next = tok;
	check_type(&new);
	return (i);
}

static void	create_redir_token(t_token *tok, char *tmp)
{
	int	i;
	int	j;

	i = 0;
	while (tmp[i])
	{
		j = 0;
		if (tmp[i] == '<' || tmp[i] == '>')
			j = redir_token(tok, tmp + i);
		i += j;
		i++;
	}
	free(tmp);
}

void	get_redir_token(t_token *tok)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	while (tok->line[i] != ')')
		i++;
	tmp = ft_substr(tok->line, i + 1, ft_strlen(tok->line + i));
	tmp1 = tok->line;
	tmp2 = ft_substr(tok->line + 1, 0, i - 1);
	free(tmp1);
	tok->line = tmp2;
	create_redir_token(tok, tmp);
}
