/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_arrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:52:36 by jihonkim          #+#    #+#             */
/*   Updated: 2023/01/03 13:58:07 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_wild(char *wild_str, char *file_name)
{
	int	wild_len;
	int	file_len;
	int	i;

	wild_len = ft_strlen(wild_str);
	file_len = ft_strlen(file_name);
	i = 0;
	while (i < wild_len && i < file_len && wild_str[i] == file_name[i])
		i++;
	if (i == wild_len && i == file_len)
		return (1);
	else if (i == wild_len && i != file_len)
		return (0);
	if (wild_str[i] == '*')
	{
		if (is_wildsub(wild_str, file_name, i))
			return (1);
	}
	return (0);
}

int	is_wildsub(char *wild_str, char *file_name, int index)
{
	int	i;

	i = 0;
	while (index + i <= (int)ft_strlen(file_name))
	{
		if (is_wild(&wild_str[index + 1], &file_name[index + i]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	cnt_cwd_wild(t_token *tok, char *wild_str)
{
	struct dirent	*file;
	DIR				*dir_ptr;
	char			*tmp;
	int				i;

	i = 0;
	tmp = getcwd(0, 4096);
	dir_ptr = opendir_util(tmp, tok);
	if (dir_ptr == 0)
		return (-1);
	file = readdir(dir_ptr);
	while (file != NULL)
	{
		if (file->d_name[0] != '.' && is_wild(wild_str, file->d_name))
		i++;
		file = readdir(dir_ptr);
	}
	closedir(dir_ptr);
	free(tmp);
	return (i);
}

void	fill_arrs(t_token *tok, char *wild_str, char **arrs)
{
	struct dirent	*file;
	DIR				*dir_ptr;
	char			*tmp;
	int				i;

	i = 0;
	tmp = getcwd(0, 4096);
	dir_ptr = opendir_util(tmp, tok);
	if (dir_ptr == 0)
		return ;
	file = readdir(dir_ptr);
	while (file != NULL)
	{
		if (file->d_name[0] != '.' && is_wild(wild_str, file->d_name))
		{
			arrs[i] = ft_strdup(file->d_name);
			i++;
		}
		file = readdir(dir_ptr);
	}
	arrs[i] = NULL;
	free(tmp);
	closedir(dir_ptr);
}

char	**make_arrs_with_wild(t_token *tok, char *wild_str)
{
	char	**arrs;
	int		i;
	int		size;

	i = 0;
	size = cnt_cwd_wild(tok, wild_str);
	arrs = (char **)malloc(sizeof(char *) * (size + 1));
	fill_arrs(tok, wild_str, arrs);
	return (arrs);
}
