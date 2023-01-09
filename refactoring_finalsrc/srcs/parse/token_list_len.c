/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 20:23:15 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/08 11:52:30 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_list_len(t_token *token)
{
	int	len;

	len = 0;
	while (token)
	{
		len++;
		token = token->next;
	}
	return (len);
}
