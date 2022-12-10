/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:22:19 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/10 05:37:29 by ko               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_info	*new_info()
{
	t_info	*new;

	new = (t_info *)malloc(sizeof(t_info));
	if (!new)
		throw_error(MALLOC_ERR);
	new->env_list = 0;
	new->old_term = 0;
	new->path = 0;
	new->exit_num = 0;
	new->stdio_backup[0] = dup(STDIN_FILENO);
	new->stdio_backup[1] = dup(STDOUT_FILENO);
	return (new);
}

void	leak(void)
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **envp)
{
	// atexit(leak);
	t_info	*info;

	info = new_info();
	initial(info, envp);
	loop(info);
	return (0);
}
