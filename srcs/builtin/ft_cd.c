/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:07:18 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/08 18:17:48 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_token *token)
{
	t_env_list	*env_list;
	char	*prev_pwd;
	char	*cur_pwd;
	char	*tmp;
	env_list = token->info->env_list;
	
	tmp = calloc(4096, sizeof(char));
	prev_pwd = ft_getenv(env_list, "PWD");
	cur_pwd = getcwd(tmp, 4096);
	ft_putenv(env_list, "PWD", cur_pwd, 0);
	ft_putenv(env_list, "OLDPWD", prev_pwd, 0);
	free(tmp);
	free(prev_pwd);
	free(cur_pwd);
}

void	ft_cd(t_token *token)
{
	char		*home_path;
	t_env_list	*env_list;

	env_list = token->info->env_list;
	home_path = ft_getenv(env_list, "HOME");
	if (ft_strncmp(home_path, "", 1) == 0)
		throw_error_message("cd", NULL, "HOME not set", 1);
	else if (token->cmd[1]) // path 가 있을 때
	{
		if (chdir(token->cmd[1]) == -1)
			throw_error_message("cd", token->cmd[1], "No such file or directory", 1);
		else
			errno = 0;
	}
	else // path가 home일 때
	{
		if (chdir(home_path) == -1)
			throw_error_message("cd", home_path, "No such file or directory", 1);
		else
			errno = 0;
	}
	// update_pwd(token);
	free(home_path);
}