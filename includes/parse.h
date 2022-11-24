/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:25:03 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/24 14:26:51 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum e_oper_type	t_oper_type;
typedef enum e_comma_type	t_comma_type;
typedef enum e_brachek_type	t_brachek_type;
typedef enum e_redir_type	t_redir_type;

enum e_oper_type
{
	NO_TYPE,
	TCMD,
	TOUT, //>
	TADDOUT, //>>
	TIN, //<
	TDOC, //<<
	TPIPE, //|
	TOR, //||
	TAND, //&
	TDAND, //&&
	TSEMI, //;
	TOBRACH, // (
	TCBRACH, // )
};

enum e_comma_type
{
	NO_COM,
	ONE_COM,
	TWO_COM,
};

enum e_brachek_type //타입에러때문에 ONE_COM을 가져왔습니다.
{
	NO_BRACHEK,
	ONE_COMM,
	TWO_COMM,
	O_BRACHEK,
	C_BRACHEK,
};

enum e_redir_type
{
	NO_DIREC,
	O_DIREC = 5,
	C_DIREC,
};

typedef struct s_token
{
	t_oper_type			type;
	char				**cmd;
	char				*line;
	struct s_token		*next;
	struct s_token		*prev;
	struct s_token		*right;
	struct s_token		*left;
	t_comma_type		comma_type;
}	t_token;

t_token			*ft_tokenlast(t_token *lst);

// is_type
t_brachek_type	ft_is_brachek(char c);
t_comma_type	ft_is_comma(char c);
t_brachek_type	ft_is_comma_brachek(char c);
t_redir_type	ft_is_redir(char c);

// oper_type
void			check_type(t_token **token);
void			set_type(t_token **token, char oper, t_oper_type one, t_oper_type two);
t_oper_type		check_operator(char c);

// cmd
void			push_index_len_redirection(char *line, int *index);
char			**ft_split_cmd(char *line);
void			set_cmd(t_token **token);


// init_token
void			init_token(char *line);
void			create_a_token(t_token **token, char **line);
int				seperate_token(char *line);
t_token			*new_token(void);
int				start_is_seperator(char *line);
void			new_push_index_until_space(char *line, int *index, t_brachek_type type);
t_token 		*ft_tokenstart(t_token *lst);

// test -- 지울것
void			func(char *s);
void			ft_tokeniter(t_token *lst, void (*f)(char *));

// parse_utility
void			push_index_until_space(char *line, int *index);
int				count_space_out_of_comma(char *str);
char			*ft_strdup_without_check_comma(char *s, int start, int len);
void			pull_until_same_comma(char *str, int *i, t_comma_type flag);

// redirection
void			set_type_remove_operator(t_token **token);

#endif