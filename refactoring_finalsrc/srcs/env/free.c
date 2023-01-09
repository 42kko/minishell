/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:01:28 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/08 11:51:17 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*free_a_node_of_env_list(t_env_list *env_list)
{
	t_env_list	*next;

	next = env_list->next;
	free(env_list->key);
	free(env_list->value);
	free(env_list);
	return (next);
}

void	free_env_list(t_env_list *env_list)
{
	while (env_list)
		env_list = free_a_node_of_env_list(env_list);
}
