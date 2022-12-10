/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 09:45:37 by ko                #+#    #+#             */
/*   Updated: 2022/12/10 13:53:23 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_dir(struct dirent *file, DIR *dir_ptr, char ***src, int i)
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
	}
	j--;
	return (j);
}

static int	write_wild(char ***dst, char ***src, t_token *tok, char *pwd)
{
	struct dirent	*file;
	DIR				*dir_ptr;
	int				i;
	int				j;
	int				flag;

	i = 0;
	j = 0;
	flag = 0;
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

static int	edit_wild(t_token *tok, int cnt, int *i)
{
	char	**new;
	char	**tmp;
	char	*pwd;

	printf("d\n");
	tmp = tok->cmd;
	cnt += cnt_cmd(tok->cmd);
	cnt += cnt_pwd(tok->info, tok, &pwd);
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
	*i += cnt - 2;
	free_cmd(tmp);
	free(pwd);
	return (0);
}

int	expansion_wild(t_token *tok)
{
	int	i;

	while (tok)
	{
		i = 0;
		if (tok->type == TCMD)
		{
			while (tok->cmd[i])
			{
				if (check_wild(tok->cmd[i]) == 1)
				{
					if (edit_wild(tok, 0, &i) < 0)
						return (-1);
				}
				i++;
			}
		}
		tok = tok->next;
	}
	return (0);
}
