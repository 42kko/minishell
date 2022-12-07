/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:39:32 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/07 14:42:38 by kko              ###   ########.fr       */
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

void	new_push_index_until_space(char *line, int *index, \
t_brachek_type type, t_token *tok)
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
	throw_error_syntax(SYNTAX_ERR, tok);
}

int	start_is_seperator(char *line, t_token *tok)
{
	t_brachek_type	type;

	if (*line == '|' || *line == '&')
	{
		if (*(line + 1) != 0 && (*(line + 1) == '&' || *(line + 1) == '|'))
			return (2);
		if (*line == '&')
			throw_error_syntax(SYNTAX_ERR, tok);
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
	new->fd_in = -1;
	new->fd_out = -1;
	new->errn = 0;
	new->err_flag_syn = 0;
	new->err_flag_notfound = 0;
	new->token_type = 0;
	return (new);
}

int	seperate_token(char *line, t_token *tok)
{
	int	i;

	i = 0;
	if (start_is_seperator(line, tok)) //에러 판단부
		return (start_is_seperator(line, tok));
	while (line[i])
	{
		if (ft_is_comma_brachek(line[i]) != NO_BRACHEK)
			new_push_index_until_space(line, &i, ft_is_comma_brachek(line[i]), tok); //에러판단부
		else if (line[i] == '|' || line[i] == '&')
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
	i = seperate_token(*line, new);
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

int	identify_built_exec(t_token *tok) //빌트인 - 1 , exec - 0
{
	if (tok->type != TCMD)
		return (-1);
	if (ft_strncmp(tok->cmd[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(tok->cmd[0], "$?", 3) == 0)
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
	char		**ret;
	t_env_list	*tmp;

	tmp = info->env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH", 5) == 0)
			break ;
		tmp = tmp->next;
	}
	ret = ft_split(tmp->value, ':');
	return (ret);
}

void	not_found(char *cmd)
{
	printf("command nt found: %s\n", cmd);
}

char	*write_path(char *cmd, t_token *tok)
{
	int		i;
	char	*tmp;
	char	*tmp1;

	if (cmd[0] == '\0')
		return (0);
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

void	check_redir_data(t_token *tok)
{
	int	i;

	while (tok)
	{
		i = 0;
		if (tok->type == TDOC || tok->type == TADDOUT || \
		tok->type == TIN || tok->type == TOUT)
		{
			while (tok->line[i])
			{
				if (tok->line[i] != '<' && tok->line[i] != '>' && \
				tok->line[i] != ' ' && tok->line[i] != '\0')
					break ;
				i++;
			}
			if (tok->line[i] == '\0')
				throw_error_syntax(SYNTAX_ERR, tok);
		}
		tok = tok->next;
	}
}

t_token	*init_token(char *line, t_info *info)
{
	t_token	*token;
	t_token	*temp;

	token = 0;
	while (*line)
		create_a_token(&token, &line, info);
	if (token->err_flag_syn == 1)
		return (token);
	temp = token;
	while (temp)
	{
		set_type_remove_operator(&temp, &token);
		temp = temp->next;
	}
	check_redir_data(token);
	errno = 0;
	return (token);
}