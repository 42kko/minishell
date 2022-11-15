#include "test.h"

t_token	*new_token(void)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->type = 0;
	new->cmd = 0;
	new->line = 0;
	new->input = 0;
	new->output = 0;
	new->next = 0;
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
		if (*line != '<' || *line != '>' || *line != ' ')
			plag = 1;
		if (*line == ' ' && plag == 1)
		{
			return (i);
		}
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
		{
			return(i);
		}
		else if ((*line == '<' || *line == '>') && i == 0)
		{
			return(sep_len(line));
		}
		i++;
		line++;
	}
	return (i);
}

void	first_token(t_token **token, char **line)
{
	int	i;

	(*token) = new_token();
	i = ft_sep(*line);
	(*token)->line = strndup(*line, i);
	(*line) += i;
}

void	ft_puls(t_token **token, char **line)
{
	t_token	*tail;
	t_token	*new;
	int		i;
	char	*tmp;

	i = 0;
	tmp = *line;
	if (*token == 0)
		first_token(token, line);
	else
	{
		tail = ft_lstlast(*token);
		new = new_token();
		i = ft_sep(*line);
		new->line = strndup(*line, i);
		(*line) += i;
		tail->next = new;
	}
}

void	func(char *s)
{
	printf("list : '%s'\n", s);
}

void	ft_lstiter(t_token *lst, void (*f)(char *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->line);
		lst = lst->next;
	}	
}

int main()
{
	char *tmp = "   <e ls -al -al <<b <<c <<a >Q >D >V >BA >DBF| < Makefile  | wc -l | <b cat >   out >c && ls || ls";
	char *line;
	t_token	*token;

	token = 0;
	line = strdup(tmp);
	int i = 0;
	tmp = 0;


	tmp = 
	line = ft_strtrim(line, " ");
	line = ft_strtrim(line, " ");
		// ft_puls(&token, &line);
		// printf("a\n");
		// tmp = line;
		// line = ft_strtrim(line, " ");
		// free(tmp);
		// ft_puls(&token, &line);
		// printf("a\n");
		// tmp = line;
		// line = ft_strtrim(line, " ");
		// free(tmp);
		// ft_puls(&token, &line);


	// while (*line)
	// {
	// 	ft_puls(&token, &line);
	// }
		// printf("df:%s\n", line);
		// tmp = line;
		// line = ft_strtrim(line, " ");
		// free(tmp);
		// printf("df:%s\n", line);
	ft_lstiter(token, func);
}