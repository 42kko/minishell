/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:25:03 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/07 02:43:20 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum e_oper_type	t_oper_type;
typedef enum e_comma_type	t_comma_type;
typedef enum e_brachek_type	t_brachek_type;
typedef enum e_redir_type	t_redir_type;
typedef enum e_wave_type	t_wave_type;

enum e_wave_type
{
	NO_WAVE,
	ONLY_WAVE,
	MAYBE_HOME,
};

enum e_oper_type
{
	NO_TYPE,
	TCMD,
	TOUT, //>
	TADDOUT, //>>
	TIN, //<
	TDOC, //<<
	NO_REDIR, //리다이렉션없음
	TPIPE, //|
	TOR, //||
	TAND, //&
	TDAND, //&&
	TSEMI, //;
	TBRACH, // ( )
	O_COM, // '
	T_COM, // "
	TRDYCMD,
	TNOCMD,
};

enum e_sigset
{
	BASH,
	CHILD,
	DOC,
	DFL,
	FORK,
	IGN,
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

typedef struct s_pipe
{
	int	cnt;
	int	*p;
}	t_pipe;

typedef struct s_keys
{
	char			*key;
	char			*value;
	int				key_len;
	int				value_len;
	int				start_idx;
	struct s_keys	*next;
}	t_keys;

typedef struct s_token
{
	int					err_flag_syn;
	int					err_flag_notfound;
	int					token_type;
	int					fd_out;
	int					fd_in;
	int					exit_num;
	char				**cmd;
	char				*line;
	struct s_token		*next;
	struct s_token		*prev;
	struct s_token		*right;
	struct s_token		*left;
	struct s_token		*parent;
	t_info				*info;
	t_oper_type			type;
	t_comma_type		comma_type;
	int	std_in_backup;
	int	std_out_backup;
}	t_token;

typedef struct s_parse_tmp
{
	t_comma_type	type;
	int				*i;
	int				*j;
	int				len;
	char			*s;
	char			*str;
}	t_parse_tmp;

t_token			*ft_tokenlast(t_token *lst);

// is_type
t_brachek_type	ft_is_brachek(char c);
t_comma_type	ft_is_comma(char c);
t_brachek_type	ft_is_comma_brachek(char c);
t_redir_type	ft_is_redir(char c);

// oper_type
void			check_type(t_token **token);
void			set_type(t_token **token, \
char oper, t_oper_type one, t_oper_type two);
t_oper_type		check_operator(char c);
t_oper_type		check_operator_for_env(char c);
void			check_subshells(t_token **token, int i);
int				have_brachek(char *line, t_token *tok);
t_oper_type		first_check_operator(char c);

// cmd
char			**ft_split_cmd(t_token **token, char *line);
void			set_cmd(t_token **token);

// init_token
t_token			*init_token(char *line, t_info *info);
void			create_a_token(t_token **token, char **line, t_info *info);
int				seperate_token(char *line, t_token *tok);
t_token			*new_token(t_info *info);
int				start_is_seperator(char *line, t_token *tok);
void			new_push_index_until_space(char *line,\
int *index, t_brachek_type type, t_token *tok);
t_token			*ft_tokenstart(t_token *lst);
int				identify_built_exec(t_token *tok);


// parse_utility
char			*cpy_wout_com(t_token **token, char *s, \
int start, int len);
int				token_list_len(t_token *token);

// push_inde_about_comma
int				count_space_out_of_comma(char *str);
void			push_index_until_space_or_oper(char *line, int *index);

// redirection
void			set_type_remove_operator(t_token **token, t_token **first);

// ft_strjoin_space
char			*ft_strjoin_space(char const *s1, char const *s2);

// tree
t_token			*cmd_tree(t_token *tok);
t_token			*get_tree(t_token *token);
void			extra_work_tree(t_token *tok);
t_token			*next_token(t_token *token);
t_token			*prev_token(t_token *token);
void			select_oper(t_token *tok, t_oper_type *oper1, \
t_oper_type *oper2, t_oper_type *oper3);

// run
void	throw_error_syntax(t_error_type type, t_token *tok);
void			run_shell(t_token *tok);
int				run(char *line, t_info *info);

// run_pipe
int	open_util(t_oper_type type, char *line);
void	ft_redir(t_token *lst, t_pipe *pip);
void	io_ctl(t_pipe *pip, int i, t_token *tok);
void	ft_child(t_token *tok, int i, t_pipe *pip);
void	ft_parent(int i, t_pipe *pip);
void	new_pipe(t_pipe *pip);
void	run_pipe(t_token *tok);


// check_env
char			*change_key_to_value(char *cmd, t_keys *keys);
void			free_keys(t_keys *keys);

// delete_comma_check_env
void			delete_comma_check_env(t_token **token, \
t_keys **keys, t_parse_tmp *tmp);

// token_list_len
int				token_list_len(t_token *token);

// malloc_utils
char			*malloc_str(int len);
char			*malloc_changed_str(char *cmd, t_keys *keys);

// check_wave
void			change_wave_to_home(t_token **token, char **arr, int i);
t_wave_type		check_is_wave(t_token **token, char **arr, int *left, int *right);

// cut_cmd
void			cut_cmd(t_token **token, char **arr, int *left, int *right);


// test -- 지울것
void			ft_tokeniter(t_token *lst);
void			viewtree(t_token *tok);
void			show_list_type_data(t_token *lst);
void			printf_key(t_keys *keys);
void			printf_env(char **arr);

// open_dir
void	writedoc(char *limiter, int *p);
int		open_util(t_oper_type type, char *line);
int		here_doc(char *limiter);
char	*find_redir(char *s);
void	open_out(t_token *tok, t_token *tmp);
void	open_in(t_token *tok, t_token *tmp);
void	start_open(t_token *tok);
void	open_redir(t_token *tok);

//path
void	add_path(t_token *tok, t_info *info);

//signal
void	set_signal(int num);

#endif