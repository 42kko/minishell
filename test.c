#include "test.h"

typedef struct s_token
{
	unsigned char		type;
	char				**cmd;
	char				*line;
	char				*input;
	char				*output;
	char				*doc;
	struct s_token		*next;
}	t_token;

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

char	*ft_strndup(char *s, int i)
{
	char	*ret;

	if (*s == 0)
	{
		return (0);
	}
	ret = (char *)malloc(sizeof(char) * i + 1);
	if (!ret)
		return (0);
	strlcpy(ret, s, i + 1);
	return (ret);
}

int	ft_sep(char *line)
{
	if (*line == '|' || *line == '&' || *line == ';')
		return (1);
	return (0);
}

t_token *ft_tail(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while(tmp->next != 0)
		tmp = tmp->next;
	return (tmp);
}

char	*ft_puls(t_token *token, char *line)
{
	t_token *tail;
	t_token *new;
	char *tmp;

	tmp = line;
	new = new_token();
	tail = ft_tail(token);
	int i = 0;
	while (*line && *(line + 1))
	{
		if (ft_sep(line) != 0)
		{
			if (i == 0)
			{
				if (ft_sep(line + 1) != 0)
				{
					i++;
					line++;
				}
				i++;
				line++;
			}
			break;
		}
		i++;
		line++;
	}
	if (*(line + 1) == 0)
	{
		i++;
		line++;
	}
	new->line = ft_strndup(tmp, i);
	tail->next = new;
	return (line);
}

int	strlen_util(char *s)
{
	int i = 0;
	char *tmp = s;
	int plag = 0;

	while (tmp[i])
	{
		if (tmp[i] == ' ' && plag == 1)
			break ;
		if (tmp[i] != ' ')
			plag = 1;
		i++;
	}
	return (i);
}

char	*new_line(char *line, int i, int len, int fixed)
{
	char *tmp = line;
	int lens;
	char *new;
	int j = 0;

	lens = strlen(line);
	new = (char *)malloc(sizeof(char) * lens - fixed - len + 1);
	new[lens-fixed-len] = 0;
	while (line[j] && j != i)
	{
		new[j] = line[j];
		j++;
	}
	while (line[j + fixed + len])
	{
		new[j] = line[j + fixed + len];
		j++;
	}
	free(tmp);
	tmp = ft_strtrim(new, " ");
	free(new);
	return (tmp);
}

void	taping_cmd(t_token *tok)
{
	int i = 0;
	char *tmp = tok->line;
	tok->line = ft_strtrim(tok->line, " ");
	free(tmp);
	int j = 0;
	while (tok->line[i])
	{
		j = 0;
		if (tok->line[i] == '>' && tok->line[i + 1] == '>')
		{
			tok->type |= TADDOUT;
			tok->output = ft_strndup(&(tok->line[i + 2]), strlen_util(&(tok->line[i + 2])));
			tmp = tok->output;
			tok->output = ft_strtrim(tok->output, " ");
			free(tmp);
			tok->line = new_line(tok->line, i, strlen_util(&(tok->line[i + 2])), 2);
			// j = strlen_util(&(tok->line[i + 2])) + 2;
		}
		else if (tok->line[i] == '>' && tok->line[i + 1] != '>')
		{
			tok->type |= TOUT;
			tok->output = ft_strndup(&(tok->line[i + 1]), strlen_util(&(tok->line[i + 1])));
			tmp = tok->output;
			tok->output = ft_strtrim(tok->output, " ");
			free(tmp);
			tok->line = new_line(tok->line, i, strlen_util(&(tok->line[i + 1])), 1);
			// j = strlen_util(&(tok->line[i + 1])) + 1;
		}
		else if (tok->line[i] == '<' && tok->line[i + 1] == '<')
		{
			tok->type |= TDOC;
			tok->doc = ft_strndup(&(tok->line[i + 2]), strlen_util(&(tok->line[i + 2])));
			tmp = tok->doc;
			tok->doc = ft_strtrim(tok->doc, " ");
			free(tmp);
			tok->line = new_line(tok->line, i, strlen_util(&(tok->line[i + 2])), 2);
			// j = strlen_util(&(tok->line[i + 2])) + 2;
		}
		else if (tok->line[i] == '<' && tok->line[i + 1] != '<')
		{
			tok->type |= TIN;
			tok->input = ft_strndup(&(tok->line[i + 1]), strlen_util(&(tok->line[i + 1])));
			tmp = tok->input;
			tok->input = ft_strtrim(tok->input, " ");
			free(tmp);
			tok->line = new_line(tok->line, i, strlen_util(&(tok->line[i + 1])), 1);
			// j = strlen_util(&(tok->line[i + 1])) + 1;
		}
		i++;
		i = i + j;
	}
}

void	taping(t_token *tok)
{
	if (*(tok->line) == '|' && *(tok->line + 1) == 0)
	{
		tok->type = TPIPE;
		// return ;
	}
	else if (*(tok->line) == '|' && *(tok->line + 1) == '|')
	{
		tok->type = TOR;
		// return ;
	}
	else if (*(tok->line) == '&' && *(tok->line + 1) != 0)
	{
		tok->type = TAND;
		// return ;
	}
	else
		taping_cmd(tok);
	// printf("sdf:%s\n", tok->line);
}

int main()
{
	char *tmp = "<e ls -al -al <<b <<c <<a >Q >D >V >BA >DBF| < Makefile  | wc -l | <b cat >   out >c && ls || ls";
	char *line;
	t_token	*token;

	token = new_token();
	line = strdup(tmp);
	int i = 0;
	while (*line)
	{
		if (ft_sep(line) != 0)
			break;
		i++;
		line++;
	}
	token->line = ft_strndup(tmp, i);
	while (*line)
		line = ft_puls(token, line);
	t_token *tok;
	tok = token;
	while (tok != 0)
	{
		taping(tok);
		tok = tok->next;
	}
	tok = token;
	while (tok != 0)
	{
		if (ft_isprint(*(tok->line)) == 1)
		{
			tok->type |= TCMD;
			tok->cmd = ft_split(tok->line, ' ');
		}
		tok = tok->next;
	}
	printf("d1:%s\n", token->cmd[0]);
	printf("d1:%s\n", token->cmd[1]);
	printf("d1:%s\n", token->cmd[2]);
	printf("d1:%s\n", token->doc);
	printf("d1:%s\n", token->output);
	// printf("d1:%s\n", token->next->next->line);
	// printf("ty:%d\n", token->next->next->type);
	// printf("ty:%d\n", token->next->next->next->next->next->next->type);
	// printf("s:%s\n", token->next->next->next->next->next->next->output);

	// printf("d1:%s\n", token->line);
	// printf("d1:%s\n", token->next->line);
	// printf("d1:%s\n", token->next->next->line);
	// printf("d1:%s\n", token->next->next->input);
	// printf("d1:%s\n", token->next->next->next->line);
	// printf("d1:%s\n", token->next->next->next->next->line);
	// printf("d1:%s\n", token->next->next->next->next->next->line);
	// printf("d1:%s\n", token->next->next->next->next->next->next->line);
	// printf("d1:%s\n", token->next->next->next->next->next->next->output);
	// printf("d1:%s\n", token->next->next->next->next->next->next->input);
	// printf("d1:%s\n", token->next->next->next->next->next->next->next->line);
}
