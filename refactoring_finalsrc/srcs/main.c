/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:22:19 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/03 14:03:43 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_errno;

static t_info	*new_info(void)
{
	t_info	*new;

	new = (t_info *)malloc(sizeof(t_info));
	if (!new)
		throw_error(MALLOC_ERR);
	new->env_list = 0;
	new->old_term = malloc(sizeof(struct termios));
	new->term = malloc(sizeof(struct termios));
	new->path = 0;
	new->exit_num = 0;
	new->stdio_backup[0] = dup(STDIN_FILENO);
	new->stdio_backup[1] = dup(STDOUT_FILENO);
	return (new);
}

void	eof_exit(t_info *info)
{
	printf("exit\n");
	tcsetattr(STDIN_FILENO, TCSANOW, info->old_term);
	exit(info->exit_num);
}

int	main(int ac, char **av, char **envp)
{
	t_info	*info;

	(void)ac;
	(void)av;
	g_errno = 0;
	info = new_info();
	initial(info, envp);
	loop(info);
	return (0);
}
