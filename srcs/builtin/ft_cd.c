/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:07:18 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/12 20:20:15 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_token *token)
{
	t_env_list	*env_list;
	char		*prev_pwd;
	char		*cur_pwd;
	char		*tmp;

	env_list = token->info->env_list;
	tmp = ft_calloc(4096, sizeof(char));
	prev_pwd = ft_getenv(env_list, "PWD");
	cur_pwd = getcwd(tmp, 4096);
	ft_putenv(env_list, "PWD", cur_pwd, 0);
	ft_putenv(env_list, "OLDPWD", prev_pwd, 0);
	free(tmp);
	free(prev_pwd);
}

static void	if_cd_home(t_token *token, char *home_path)
{
	if (chdir(home_path) == -1)
	{
		throw_error_message("cd", home_path, \
		"No such file or directory", 1);
		token->info->exit_num = 1;
	}
	else
		token->info->exit_num = 0;
}

void	ft_cd(t_token *token)
{
	char		*home_path;
	t_env_list	*env_list;

	env_list = token->info->env_list;
	home_path = ft_getenv(env_list, "HOME");
	if (ft_strncmp(home_path, "", 1) == 0)
	{
		throw_error_message("cd", NULL, "HOME not set", 1);
		token->info->exit_num = 1;
	}
	else if (token->cmd[1])
	{
		if (chdir(token->cmd[1]) == -1)
		{
			throw_error_message("cd", token->cmd[1], \
			"No such file or directory", 1);
			token->info->exit_num = 1;
		}
		else
			token->info->exit_num = 0;
	}
	else
		if_cd_home(token, home_path);
	update_pwd(token);
	free(home_path);
}
