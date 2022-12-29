/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 09:45:40 by ko                #+#    #+#             */
/*   Updated: 2022/12/30 02:48:24 by ko               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

DIR	*opendir_util(char *pwd, t_token *tok)
{
	DIR				*dir_ptr;

	dir_ptr = opendir(pwd);
	if (dir_ptr == NULL)
	{
		free(pwd);
		err_msg("opendir err", tok, "*");
		return (0);
	}
	return (dir_ptr);
}

int	check_wild(char *s)
{
	int	i;
	int	flag;

	i = 0;
	while (s[i])
	{
		if (s[i] == '*')
			flag = 1;
		else
			return (0);
		i++;
	}
	return (flag);
}

int	cnt_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	i--;
	return (i);
}

int	cnt_pwd(t_token *tok, char **pwd)
{
	struct dirent	*file;
	DIR				*dir_ptr;
	char			*tmp;
	int				i;

	i = 0;
	tmp = getcwd(0, 4096);
	*pwd = tmp;
	dir_ptr = opendir_util(tmp, tok);
	if (dir_ptr == 0)
		return (-1);
	file = readdir(dir_ptr);
	while (file != NULL)
	{
		if (file->d_name[0] != '.')
			i++;
		file = readdir(dir_ptr);
	}
	closedir(dir_ptr);
	return (i);
}
