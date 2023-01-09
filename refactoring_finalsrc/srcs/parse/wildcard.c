/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 09:45:37 by ko                #+#    #+#             */
/*   Updated: 2022/12/30 17:23:56 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_dir(struct dirent *file, DIR *dir_ptr, char ***src, int i)
{
	int	j;

	j = 0;
	file = readdir(dir_ptr);
	while (file != NULL)
	{
		if (file->d_name[0] != '.')
		{
			src[0][i + j] = ft_strdup(file->d_name);
			j++;
		}
		file = readdir(dir_ptr);
	}
	j--;
	return (j);
}

int	write_wild(char ***dst, char ***src, t_token *tok, char *pwd)
{
	struct dirent	*file;
	DIR				*dir_ptr;
	int				i;
	int				j;
	int				flag;

	zero_parameter1(&i, &j, &flag);
	file = 0;
	dir_ptr = opendir_util(pwd, tok);
	if (dir_ptr == 0)
		return (-1);
	while (dst[0][i])
	{
		if (check_wild(dst[0][i]) != 1 || flag == 1)
			src[0][i + j] = ft_strdup(dst[0][i]);
		else if (flag == 0)
		{
			j += write_dir(file, dir_ptr, src, i);
			flag = 1;
		}
		i++;
	}
	closedir(dir_ptr);
	return (0);
}

int	what_wild(char **new)
{
	int	i;

	i = 0;
	while (new[i])
	{
		if (check_wild(new[i]) == 1)
			break ;
		i++;
	}
	return (i - 1);
}

int	edit_wild(t_token *tok, int cnt, int *i)
{
	char	**new;
	char	**tmp;
	char	*pwd;

	tmp = tok->cmd;
	cnt += cnt_cmd(tok->cmd);
	cnt += cnt_pwd(tok, &pwd);
	new = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!new)
		throw_error(MALLOC_ERR);
	new[cnt] = 0;
	if (write_wild(&(tok->cmd), &new, tok, pwd) < 0)
	{
		free(new);
		return (-1);
	}
	tok->cmd = new;
	*i = what_wild(new);
	free_cmd(tmp);
	free(pwd);
	return (0);
}

int	free_wild(char *tmp, int ret)
{
	free(tmp);
	return (ret);
}
