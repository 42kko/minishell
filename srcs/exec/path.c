/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:40:34 by kko               #+#    #+#             */
/*   Updated: 2022/12/08 23:44:37 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**info_get_path(t_info *info)
{
	char		**ret;
	t_env_list	*tmp;

	tmp = info->env_list;
	while (tmp)
	{
		if (tmp->key && ft_strncmp(tmp->key, "PATH", 5) == 0)
			break ;
		tmp = tmp->next;
	}
	ret = ft_split(tmp->value, ':');
	return (ret);
}

int	ft_access(const char *pathname, int mode)
{
	struct stat	buf;
	int			r;
	int			w;
	int			x;

	r = 0;
	w = 0;
	x = 0;
	if (stat(pathname, &buf) < 0)
		return (-1);
	if ((buf.st_mode & S_IRUSR) != 0)
		r = 4;
	if ((buf.st_mode & S_IWUSR) != 0)
		w = 2;
	if ((buf.st_mode & S_IXUSR) != 0)
		x = 1;
	if (r == mode || w == mode || x == mode || r + w == mode || r + x == mode \
	|| w + x == mode || r + w + x == mode || mode == 0)
		return (0);
	return (-1);
}

void	not_found(char *cmd)
{
	errno = 127;
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}

char	*write_path(char *cmd, t_token *tok)
{
	int		i;
	char	*tmp;
	char	*tmp1;

	if (ft_access(cmd, 1) == 0 && ft_strchr(cmd, '/') != 0)
		return (cmd);
	i = 0;
	tmp1 = ft_strjoin("/", cmd);
	while (tok->info->path[i])
	{
		tmp = ft_strjoin(tok->info->path[i], tmp1);
		if (ft_access(tmp, 1) == 0)
		{
			free(cmd);
			free(tmp1);
			return (tmp);
		}
		free(tmp);
		tmp = 0;
		i++;
	}
	free(tmp1);
	not_found(cmd);
	return (cmd);
}

void	add_path(t_token *tok)
{
	if (identify_built_exec(tok) == 0 && tok->type == TCMD)
		tok->cmd[0] = write_path(tok->cmd[0], tok);
	errno = 0;
}