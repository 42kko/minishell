/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:01:28 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/09 22:12:22 by seokchoi         ###   ########.fr       */
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
