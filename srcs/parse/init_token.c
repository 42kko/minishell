/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:39:32 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/01 22:54:14 by ko               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_tokenstart(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}

int	read_redir(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|' || line[i] == '&' || line[i] == ';')
		i++;
	}
	return (i);
}

void	new_push_index_until_space(char *line, int *index, t_brachek_type type)
{
	(*index)++;
	if (type == O_BRACHEK)
		type = C_BRACHEK;
	while (line[*index] != '\0')
	{
		if (ft_is_comma_brachek(line[*index]) == type)
			return ;
		(*index)++;
	}
	throw_error(SYNTAX_ERR);
}

int	start_is_seperator(char *line)
{
	t_brachek_type	type;

	if (*line == '|' || *line == '&' || *line == ';')
	{
		if (*(line + 1) != 0 && (*(line + 1) == '&' || *(line + 1) == '|'))
			return (2);
		if (*line == '&')
			throw_error(SYNTAX_ERR);
		return (1);
	}
	return (0);
}

t_token	*new_token(t_info *info)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		throw_error(MALLOC_ERR);
	new->type = NO_TYPE;
	new->cmd = NULL;
	new->line = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->left = NULL;
	new->right = NULL;
	new->comma_type = NO_COM;
	new->parent = NULL;
	new->info = info;
	return (new);
}

int	seperate_token(char *line)
{
	int	i;

	i = 0;
	if (start_is_seperator(line))
		return (start_is_seperator(line));
	while (line[i])
	{
		if (ft_is_comma_brachek(line[i]) != NO_BRACHEK)
			new_push_index_until_space(line, &i, ft_is_comma_brachek(line[i]));
		else if (line[i] == '|' || line[i] == '&' || line[i] == ';')
			return (i);
		i++;
	}
	return (i);
}

void	create_a_token(t_token **token, char **line, t_info *info)
{
	t_token	*tail;
	t_token	*new;
	int		i;
	char	*tmp;

	i = 0;
	tmp = *line;
	while (**line == ' ' && **line != 0)
		(*line)++;
	new = new_token(info);
	i = seperate_token(*line);
	new->line = ft_substr(*line, 0,i);
	(*line) += i;
	if (*token == 0)
		(*token) = new;
	else
	{
		tail = ft_tokenlast(*token);
		new->prev = tail;
		tail->next = new;
	}
}

void	check_syntax()
{
	// | || && ; (리다이렉션인데 파일 이름이 없는 애들) 처음에 오면 안되는 애들  
	// 연산자가 연속으로 오는 애들
	// & 하나만 들어온경우
	//토큰생성시 미리 처리해서 없어도 될듯함.
}

int	identify_built_exec(t_token *tok) //빌트인 - 1 , exec - 0
{
	if (tok->type != TCMD)
		return (-1);
	if (ft_strncmp(tok->cmd[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "export", 3) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "unset", 3) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "env", 3) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "exit", 3) == 0)
		return (1);
	else
		return (0);
}

int	ft_access(const char *pathname, int mode)
{
	struct stat buf;
	int	r;
	int	w;
	int	x;

	r = 0;
	w = 0;
	x = 0;
	if(stat(pathname, &buf) < 0)
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

char	**info_get_path(t_info *info)
{
	char	**ret;

	while (info->env_list)
	{
		if (ft_strncmp(info->env_list->key, "PATH", 5) == 0)
			break ;
		info->env_list = info->env_list->next;
	}
	ret = ft_split(info->env_list->value, ':');
	return (ret);
}

char	*write_path(char *cmd, t_info *info)
{
	int		i;
	char	**path;
	char	*tmp;
	char	*tmp1;

	if (ft_access(cmd, 1) == 0 && ft_strchr(cmd, '/') != 0)
		return (cmd);
	path = info_get_path(info);
	i = 0;
	tmp1 = ft_strjoin("/", cmd);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], tmp1);
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
	return (cmd);
}

void	add_path(t_token *tok, t_info *info)
{
	if (tok == 0)
		return ;
	if (identify_built_exec(tok) == 0 && tok->type == TCMD)
		tok->cmd[0] = write_path(tok->cmd[0], info);
	add_path(tok->next, info);
}

t_token	*init_token(char *line, t_info *info)
{
	t_token	*token;
	t_token	*temp;

	token = 0;
	while (*line)
		create_a_token(&token, &line, info);
	temp = token;
	while (temp)
	{
		set_type_remove_operator(&temp, &token);
		temp = temp->next;
	}

	add_path(token, info);
	ft_tokeniter(token);
	// check_syntax(token);
	// token = get_tree(ft_tokenlast(token));
	// viewtree(token); //parent 연결 및 트리출력.
	return (token);
	// extra_work_tree(token); //괄호처리용, 아직작업중.
}