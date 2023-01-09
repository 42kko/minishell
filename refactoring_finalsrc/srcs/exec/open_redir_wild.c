/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir_wild.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:25:37 by jihonkim          #+#    #+#             */
/*   Updated: 2023/01/03 14:25:59 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_wild_redir(t_token *tok, t_token *first, int idx)
{
	char	*tmp;
	char	**tmp1;

	tmp = get_prev_line(tok, first, idx);
	if (com_wild_redir(tmp) == 0)
	{
		free(tmp);
		return ;
	}
	free(tmp);
	if (cnt_cwd_wild(tok, ft_redir(tok->line)) != 1)
	{
		tok->err_flag_redir = 2;
		throw_error_message(NULL, "*", "ambiguous redirect", 0);
		return ;
	}
	tmp1 = make_arrs_with_wild(tok, ft_redir(tok->line));
	change_lien(tok, tmp1);
	free_cmd(tmp1);
}

void	expansion_wild_redir(t_token *tok, t_token *first)
{
	int		i;
	int		j;

	j = 0;
	while (tok)
	{
		i = 0;
		while (tok->line[i])
		{
			if (tok->line[i] == '*')
			{
				edit_wild_redir(tok, first, j);
				break ;
			}
			i++;
		}
		if (tok->err_flag_redir == 2)
			return ;
		tok = tok->next;
		j++;
	}
}
