/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 09:45:37 by ko                #+#    #+#             */
/*   Updated: 2022/12/30 10:50:51 by kko              ###   ########.fr       */
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
		file = readdir(dir_ptr);
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

static int	what_wild(char **new)
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

static int	edit_wild(t_token *tok, int cnt, int *i)
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

char	*set_tok_cmd(t_token *tok, int i)
{
	int		j;
	char	*ret;

	j = 0;
	while (tok->line[i + j] != 0 && tok->line[i + j] != ' ')
		j++;
	ret = (char *)malloc(sizeof(char) * j + 1);
	ret[j--] = 0;
	while (j >= 0)
	{
		ret[j] = tok->line[i + j];
		j--;
	}
	return (ret);
}

char	*get_tok_cmd(t_token *tok, int idx)
{
	int		i;
	char	*ret;

	i = 0;
	while (tok->line[i] && idx != 0)
	{
		if (tok->line[i] == '\"' || tok->line[i] == '\'')
		{
			i++;
			while (tok->line[i] != '\"' && tok->line[i] != '\'')
				i++;
		}
		if (tok->line[i] == ' ')
			idx--;
		i++;
	}
	ret = set_tok_cmd(tok, i);
	return (ret);
}

int	free_wild(char *tmp, int ret)
{
	free(tmp);
	return (ret);
}

int	com_wild(t_token *tok, int idx, char *s)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = get_tok_cmd(tok, idx);
	if (ft_strchr(tmp, '*') == 0)
		return (free_wild(tmp, 0));
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
		{
			i++;
			while (tmp[i] != '\"' && tmp[i] != '\'')
				i++;
		}
		if (tmp[i] == '*')
			return (free_wild(tmp, 1));
		i++;
	}
	return (free_wild(tmp, 0));
}

void	other_filling(t_token *tok, int *idx, char ***new, int j)
{
	char	**tmp;
	int		i;

	i = 1;
	tmp = *new;
	while (tok->cmd[i + *idx])
	{
		tmp[j] = ft_strdup(tok->cmd[i + *idx]);
		i++;
	}
}

char	**filling_cmd(t_token *tok, int *idx, char **tmp, int cnt)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = (char **)malloc(sizeof(char *) * (cnt + 1));
	new[cnt] = 0;
	while (new[i] && i < *idx)
	{
		new[i] = ft_strdup(tok->cmd[i]);
		i++;
	}
	while (tmp[j])
	{
		new[i] = ft_strdup(tmp[j]); // i = 1 j = 0
		j++;
		i++;
	}
	*idx = i - 1;
	other_filling(tok, idx, &new, i);
	return (new);
}

int is_wildsub(char *wild_str, char *file_name, int index);

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
		return 1;
	else if (i == wild_len && i != file_len)
		return 0;
	if (wild_str[i] == '*')
	{
		if (is_wildsub(wild_str, file_name, i))
			return 1;
	}
	return 0;
}

int is_wildsub(char *wild_str, char *file_name, int index)
{
	int	i;

	i = 0;
	while (index + i <= ft_strlen(file_name))
	{
		if (is_wild(&wild_str[index + 1],&file_name[index + i]))
		{
			return 1;
		}
		i++;
	}
	return 0;
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
		if (file->d_name[0] != '.' && is_wild(wild_str, file->d_name)) // 숨겨진 폴더는 제외하고 카운트
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

int	search_edit_wild(t_token *tok, int *i)
{
	char	**new;
	char	**tmp;
	char	**tmp_cmd;
	int		cnt;

	cnt = 0;
	cnt += cnt_cwd_wild(tok, tok->cmd[*i]);
	if (cnt == 0)
	{
		return (0);
	}
	cnt += cnt_cmd(tok->cmd);
	tmp = make_arrs_with_wild(tok, tok->cmd[*i]);
	new = filling_cmd(tok, i, tmp, cnt);
	int	z = 0;
	tmp_cmd = tok->cmd;
	tok->cmd = new;
	printf("new:%s\n", new[1]);
	free_cmd(tmp_cmd);
	free_cmd(tmp);
	return (0);
}

int	wild_type(t_token *tok, int *i)
{
	if (check_wild(tok->cmd[*i]) != 0)
	{
		if (edit_wild(tok, 0, i) < 0)
			return (-1);
	}
	else
	{
		if (search_edit_wild(tok, i) < 0)
			return (-1);
	}
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
				if (com_wild(tok, i, tok->cmd[i]) == 1)
				{
					if (wild_type(tok, &i) < 0)
						return (-1);
				}
				i++;
			}
		}
		tok = tok->next;
	}
	return (0);
}
