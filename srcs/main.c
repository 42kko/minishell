/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:22:19 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/22 18:48:36 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

struct termios	old_term;
struct termios	term;

t_comma_type	ft_is_comma(char c)
{
	if (c == '\'')
		return (ONE_COM);
	if (c == '\"')
		return (TWO_COM);
	return (NO_COM);
}

void	pull_until_same_comma(char *str, int *i, t_comma_type flag)
{
	char c;

	c = 0;
	if (flag == ONE_COM)
		c = '\'';
	if (flag == TWO_COM)
		c = '\"';
	if (str[*i] == c)
	{
		(*i)++;
		while (str[*i] != c && str[*i])
			(*i)++;
		if (str[*i] == c)
			(*i)++;
	}
}

void	push_index_until_space(char *line, int *index)
{
	while (line[*index] != ' ' && line[*index] != '\0')
	{
		while (ft_is_comma(line[*index]) == NO_COM && line[*index] != ' ' && line[*index] != '\0')
			(*index)++;
		while (ft_is_comma(line[*index]) != NO_COM)
			pull_until_same_comma(line, index, ft_is_comma(line[*index]));
	}
}

void	handler(int signo) //시그널핸들러
{
	if (signo == SIGINT)
	{
		printf("\n");
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
		return ;
	else if (signo == SIGTERM)
		printf("exit\n");
	return ;
}

void	initial(void) //초기작업.
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGTERM, handler);
	tcgetattr(STDIN_FILENO, &term);
	old_term = term;
	term.c_cflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(int ac, char **av, char **envp)
{
	
	initial(); //초기작업. 여기서 환경변수 및 시그널을 컨트롤할듯
	loop(); //readline 을 받아줄곳.
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
	printf("done\n");
	return (0);
}
//-----------------------------------
t_token	*new_token(void)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		throw_error(MALLOC_ERR);
	new->type = 0;
	new->cmd = 0;
	new->line = 0;
	new->next = 0;
	new->comma_type = NO_COM;
	return (new);
}



int	ft_sep(char *line)
{
	int	i;
	int	len;
	int	plag;

	i = 0;
	if (ft_is_comma(*line) != NO_COM)
	{
		push_index_until_space(line, &i);
		return (i);
	}
	if (*line == '|' || *line == '&' || *line == ';')
	{
		if (*(line + 1) != 0 && (*(line + 1) == '&' || *(line + 1) == '|'))
			return (2);
		return (1);
	}
	while (*line)
	{
		if (ft_is_comma(*line) != NO_COM)
			push_index_until_space(line, &i);
		if (*line == '|' || *line == '&')
			return (i);
		i++;
		line++;
	}
	return (i);
}

void	create_a_token(t_token **token, char **line)
{
	t_token	*tail;
	t_token	*new;
	int		i;
	char	*tmp;

	i = 0;
	tmp = *line;
	while (**line == ' ' && **line != 0)
		(*line)++;
	new = new_token();
	i = ft_sep(*line);
	new->line = ft_substr(*line, 0,i);
	(*line) += i;
	if (*token == 0)
		(*token) = new;
	else
	{
		tail = ft_tokenlast(*token);
		tail->next = new;
	}
}

void	func(char *s)
{
	printf("list : '%s'\n", s);
}

void	ft_tokeniter(t_token *lst, void (*f)(char *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->line);
		lst = lst->next;
	}	
}

t_oper_type	check_operator(char c)
{
	if (c == '|')
		return(TPIPE);
	else if (c == '&')
		return (TAND);
	else if (c == '<')
		return (TIN);
	else if (c == '>')
		return (TOUT);
	else if (c == ';')
		return(TSEMI);
	return (NO_TYPE);
}

void	set_type(t_token **token, char oper, t_oper_type one, t_oper_type two)
{
	char	*line;

	line = (*token)->line;
	if ((*token)->line[0] == oper)
	{
		if (line[1] == 0 || check_operator(line[1]) == 0)
			(*token)->type = one;
		else if (line[1] == oper && check_operator(line[2]) == 0)
			(*token)->type = two;
	}
}

void	check_type(t_token **token)
{
	set_type(token, '|', TPIPE, TOR);
	set_type(token, '&', NO_TYPE, TDAND);
	set_type(token, '<', TIN, TDOC);
	set_type(token, '>', TOUT, TADDOUT);
	if ((*token)->type == NO_TYPE)
		throw_error(SYNTAX_ERR);
}

char	*remove_outside_comma(char *cmd)
{
	if (cmd[0] == '\'')
		return (ft_strtrim(cmd, "\'"));
	if (cmd[0] == '\"')
		return (ft_strtrim(cmd, "\""));
	return (cmd);
}

char *ft_strdup_without_char(char *s, int left, int right)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(*s) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (s[i] && (i != left || i != right))
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

int	*check_exist_side_comma(t_token **token, char *str)
{
	int	left;
	int	right;
	int	*arr;

	left = 0;
	while (str[left])
	{
		if (str[left] == '\'')
		{
			(*token)->comma_type = ONE_COM;
			break ;
		}
		if (str[left] == '\"')
		{
			(*token)->comma_type = TWO_COM;
			break ;
		}
		left++;
	}
	right = ft_strlen(str) - 1;
	while (right >= 0 && right > left && (*token)->comma_type != NO_COM)
	{
		if ((str[right] == '\'' && (*token)->comma_type == ONE_COM) || (str[right] == '\"' && (*token)->comma_type == TWO_COM))
		{
			arr = malloc(sizeof(int) * 3);
			if (!arr)
				throw_error(MALLOC_ERR);
			arr[0] = left;
			arr[1] = right;
			return (arr);
		}
		right--;
	}
	if ((*token)->comma_type == ONE_COM || (*token)->comma_type == TWO_COM)
		throw_error(SYNTAX_ERR);
	(*token)->comma_type = NO_COM;
	return (NULL);
}


int	count_space_out_of_comma(char *str) // \", \' 을 스킵하고 ' ' 띄어쓰기를 찾아주는 함수
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (str[i])
	{
		while (ft_is_comma(str[i]) != NO_COM)
			pull_until_same_comma(str, &i, ft_is_comma(str[i]));
		if (str[i] == ' ')
		{
			count++;
			while (str[i] == ' ')
				i++;
		}
		else if (str[i])
			i++;
	}
	return (count);
}

char	*ft_strdup_without_check_comma(char *s, int start, int len)
{
	char			*str;
	int				i;
	int				j;
	t_comma_type	type;

	i = start;
	j = 0;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		throw_error(MALLOC_ERR);
	while (s[i] &&  j < len && i < start + len)
	{
		type = ft_is_comma(s[i]);
		if (type)
		{
			i++;
			while (s[i] && ft_is_comma(s[i]) != type && j < len)
				str[j++] = s[i++];
			if (s[i])
				i++;
		}
		else
			str[j++] = s[i++];
	}
	str[j] = '\0';
	return (str);
}

void	push_index_len_redirection(char *line, int *index)
{
	int			flag;
	t_oper_type	type;

	flag = 0;
	type = check_operator(line[*index]);
		(*index)++;
	if (check_operator(line[*index]) == type)
		(*index)++;
	else if (check_operator(line[*index]) != NO_TYPE)
		throw_error(SYNTAX_ERR);
	while (line[*index] == ' ')
		(*index)++;
	push_index_until_space(line, &(*index));
}

char	**ft_split_cmd(char *line)
{
	char	**arr;
	int		left;
	int		right;
	int		i; 

	i = 0;
	arr = malloc(sizeof(char *) * (count_space_out_of_comma(line) + 1));
	if (!arr)
		throw_error(MALLOC_ERR);
	right = 0;
	while (line[right])
	{
		left = right;
		if (line[right] == '<' || line[right] == '>')
		{
			push_index_len_redirection(line, &right);
			arr[i++] = ft_strdup_without_check_comma(line, left, right - left);
			while (line[right] == ' ')
				right++;
		}
		else
		{
			push_index_until_space(line, &right);
			if (line[right] == ' ' || line[right] == '\0')
			{
				arr[i++] = ft_strdup_without_check_comma(line, left, right - left);
				while (line[right] == ' ')
					right++;
			}
			else if (line[right])
				right++;
		}
		
	}
	arr[i] = NULL;
	return (arr);
}

void	set_cmd(t_token **token)
{
	(*token)->type = TCMD;
	(*token)->cmd = ft_split_cmd((*token)->line);
}

void	attach_redir_token(t_token	**redir_token, t_token **token, int index)
{
	t_token *new;
	
	new = new_token();
	new->line = (*token)->cmd[index];
	if (!redir_token)
		(*redir_token) = new;
	while ((*redir_token)->next)
		(*redir_token) = (*redir_token)->next;
	(*redir_token)->next = new;
}

void	devide_redir_cmd(t_token **token)
{
	t_token	*tmp_next_token;
	t_token	*redir_token;
	char	*tmp;
	int		left;
	int		right;
	
	printf("asdfasdfasdfasdfsdf\n");
	tmp_next_token = (*token)->next;
	left = 0;
	right = 0;
	redir_token = NULL;
	while ((*token)->cmd[left])
	{
		printf("홀리몰리\n");
		if (ft_is_comma((*token)->cmd[left][0]) != NO_TYPE)
			attach_redir_token(&redir_token, token, left);
		left++;
	}
	ft_tokeniter(redir_token, func);
	// while ((*token)->cmd[right])
	// 	right++;
	// right--;
	// while (left < right) // 
	// {
	// 	while (left < right) // redir을 찾는다.
	// 	{
	// 		if (ft_is_comma((*token)->cmd[left][0]) != NO_TYPE)
	// 			break;
	// 		left++;
	// 	}
	// 	while (left < right) // 앞에 redir이 있는 cmd을 찾는다.
	// 	{
	// 		if (ft_is_comma((*token)->cmd[left][0]) == NO_TYPE)
	// 			break;
	// 		right--;
	// 	}
	// }
}

void	set_type_remove_operator(t_token **token)
{
	if (check_operator((*token)->line[0]) == TPIPE || check_operator((*token)->line[0]) == TAND)
	{
		check_type(token);
	}
	else
	{
		set_cmd(token);
		devide_redir_cmd(token);
		int i = 0;
		while ((*token)->cmd[i])
		{
			printf("%d : \'%s\'\n", i, (*token)->cmd[i]);
			i++;
		}
	}
}

void create_token(char *line)
{
	// char *tmp = "         <   e ls -al -al <>          b <<c <<a >Q >D >V >BA >DBF ||& < Makefile  | wc -l | <b cat >   out >c && ls || ls";
	// char *line;
	t_token	*token;

	char *tmp;

	token = 0;
	int i = 0;

	tmp = line;
	while (*line)
		create_a_token(&token, &line);
	free(tmp);

	t_token *temp;
	temp = token;
	while (temp)
	{
		set_type_remove_operator(&temp);
		temp = temp->next;
	}
	ft_tokeniter(token, func);
}
