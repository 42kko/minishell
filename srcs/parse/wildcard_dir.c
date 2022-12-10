/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 09:45:40 by ko                #+#    #+#             */
/*   Updated: 2022/12/10 09:47:31 by ko               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

DIR	*opendir_util(char *pwd, t_token *tok)
{
	DIR				*dir_ptr;

	if ((dir_ptr = opendir(pwd)) == NULL)
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
		if (s[i] == '*' || s[i] == ' ')
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

int	cnt_pwd(t_info *info, t_token *tok, char **pwd)
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
	while ((file = readdir(dir_ptr)) != NULL)
	{
		if (file->d_name[0] != '.')
			i++;
	}
	closedir(dir_ptr);
	return (i);
}
