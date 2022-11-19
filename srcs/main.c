/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:22:19 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/18 21:27:36 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

struct termios	old_term;
struct termios	term;

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
	new->type = 0;
	new->cmd = 0;
	new->line = 0;
	new->next = 0;
	new->comma_type = NO_COM;
	return (new);
}

int	sep_len(char *line)
{
	int	i;
	int	len;
	int	plag;

	plag = 0;
	len = ft_strlen(line);
	i = 0;
	while (*line)
	{
		if (*line != '<' && *line != '>' && *line != ' ')
			plag = 1;
		if (*line == ' ' && plag == 1)
			return (i);
		i++;
		line++;
	}
	return (i);
}

int	ft_sep(char *line)
{
	int	i;
	int	len;
	int	plag;

	i = 0;
	if (*line == '|' || *line == '&' || *line == ';')
	{
		if (*(line + 1) != 0 && (*(line + 1) == '&' || *(line + 1) == '|'))
			return (2);
		return (1);
	}
	while (*line)
	{
		if ((*line == '<' || *line == '>') && i != 0)
			return (i);
		else if ((*line == '<' || *line == '>') && i == 0)
			return (sep_len(line));
		else if (*line == '|' || *line == '&')
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

int	count_space_out_of_comma(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			count++;
		else if (str[i] == '\'')
			while (str[i] != '\'' && str[i])
				i++;
		else if (str[i] == '\"')
			while (str[i] != '\"' && str[i])
				i++;
		else if (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != ' ')
			i++;
	}
	return (count + 1);
}

void	set_cmd(t_token **token)
{
	int				len;
	int				i;
	char 			*tmp;
	int				*arr;
	t_comma_type	flag;
	
	(*token)->type = TCMD;
	// 만난놈을 찾아서 지워준다.
	// 못만나면 그대로 납둔다.
	// 지원준 포인터는 계속 기억하고 있는다.

	// "p""w""d" -> ok
	// 
	printf("%d\n",count_space_out_of_comma((*token)->line));
	// ", ' 을 띵겨 넘은 ' ' 띄어쓰기를 찾아주는 함수
	(*token)->cmd = ft_split((*token)->line, ' ');
	while ((*token)->cmd[i])
	{
		arr = check_exist_side_comma(token, (*token)->cmd[i]);
		if (arr != NULL)
		{
			tmp = (*token)->cmd[i];
			(*token)->cmd[i] = ft_strdup_without_char((*token)->cmd[i], arr[0], arr[1]);
			free(arr);
			free(tmp);
		}
		i++;
	}
}

void	set_type_remove_operator(t_token **token)
{
	if (check_operator((*token)->line[0]))
	{
		check_type(token);
	}
	else
	{
		set_cmd(token);
		// 명령어일경우 연사자 따옴표처리 및 이중배열에 넣어준다
	}
}

void create_token(char *line)
{
	// char *tmp = "         <   e ls -al -al <>          b <<c <<a >Q >D >V >BA >DBF ||& < Makefile  | wc -l | <b cat >   out >c && ls || ls";
	// char *line;
	t_token	*token;

	char *tmp;

	token = 0;
	// line = ft_strdup(tmp);
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
