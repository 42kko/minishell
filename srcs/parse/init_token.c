/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:39:32 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/01 18:46:08 by marvin           ###   ########.fr       */
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
	if (ft_strncmp(tok->cmd[0], "echo", 4) == 0)
		printf("hi\n");
	return (0);
}

void	add_path(t_token *tok)
{
	if (tok == 0)
		return ;
	if (identify_built_exec(tok) != 0 && tok->type == TCMD)
	{
		return ;
	}
	add_path(tok->next);
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

	ft_tokeniter(token);
	// add_path(token);

	// identify_built_exec(token);
	printf("cmd[0]:%s\n", token->cmd[0]);
	printf("cmd[1]:%s\n", token->cmd[1]);
	// check_syntax(token);
	// token = get_tree(ft_tokenlast(token));
	// viewtree(token); //parent 연결 및 트리출력.
	return (token);
	// extra_work_tree(token); //괄호처리용, 아직작업중.
}