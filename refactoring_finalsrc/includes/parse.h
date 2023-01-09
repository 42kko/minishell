/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:25:03 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/03 13:43:29 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum e_oper_type	t_oper_type;
typedef enum e_comma_type	t_comma_type;
typedef enum e_brachek_type	t_brachek_type;
typedef enum e_redir_type	t_redir_type;
typedef enum e_wave_type	t_wave_type;
typedef struct s_keys		t_keys;
typedef struct s_token		t_token;
typedef struct s_parse_tmp	t_parse_tmp;
typedef struct s_info		t_info;
typedef struct s_env_list	t_env_list;

struct s_info
{
	struct termios	*old_term;
	struct termios	*term;
	t_env_list		*env_list;
	char			**path;
	int				exit_num;
	int				stdio_backup[2];
};

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
	TOUT,
	TADDOUT,
	TIN,
	TDOC,
	NO_REDIR,
	TPIPE,
	TOR,
	TAND,
	TDAND,
	TSEMI,
	TBRACH,
	O_COM,
	T_COM,
	TRDYCMD,
	TRDYBRACH,
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

enum e_brachek_type
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

struct s_keys
{
	char			*key;
	char			*value;
	int				key_len;
	int				value_len;
	int				start_idx;
	struct s_keys	*next;
};

struct s_token
{
	int					err_flag_syn;
	int					err_flag_redir;
	int					token_type;
	int					fd_out;
	int					fd_in;
	int					errn;
	pid_t				last_pid;
	char				**cmd;
	char				*line;
	char				*line_old;
	struct s_token		*next;
	struct s_token		*prev;
	struct s_token		*right;
	struct s_token		*left;
	struct s_token		*parent;
	t_info				*info;
	t_oper_type			type;
	t_comma_type		comma_type;
};

struct s_parse_tmp
{
	t_comma_type	type;
	int				*i;
	int				*j;
	int				len;
	char			*s;
	char			*str;
};

//check_list
void			check_redir_data(t_token *tok);
void			check_type(t_token **token);
t_oper_type		check_operator(char c);
t_oper_type		check_operator_for_env(char c);
t_oper_type		first_check_operator(char c);

//check_list2
int				check_redir(char c);
void			check_subshells(t_token **token, int i);
void			error_hunter(t_token *tok);

//check wave
t_wave_type		check_is_wave(t_token **token, \
char **arr, int *left, int *right);
void			change_wave_to_home(t_token **token, char **arr, int i);

//cmd
void			set_cmd(t_token **token);

//cut_cmd
void			cut_cmd(t_token **token, char **arr, int *left, int *right);

//ft_strjoin_space
char			*ft_strjoin_space(char const *s1, char const *s2);

//delete_comma_check_env
void			delete_comma_check_env(t_token **token, t_keys **keys, \
t_parse_tmp *tmp);

//init_token
void			new_push_index_until_space(char *line, int *index, \
t_brachek_type type, t_token *tok);
t_token			*init_token(char *line, t_info *info);

// key_util
int				ft_keycpy(char *dst, char *src, int dstsize);
t_keys			*ft_keyslast(t_keys *keys);

//is_type
t_brachek_type	ft_is_comma_brachek(char c);
t_brachek_type	ft_is_brachek(char c);
t_redir_type	ft_is_redir(char c);
t_comma_type	ft_is_comma(char c);

//malloc_utils
char			*malloc_str(int len);
char			*malloc_changed_str(char *cmd, t_keys *keys);

//oper_type
int				cnt_redir(char *line, t_token **tok);
int				push_index(char *line, int *i);
int				have_brachek(char *line, t_token *tok);
void			set_type(t_token **token, char oper, \
t_oper_type one, t_oper_type two);

//parse_utility
char			*cpy_wout_com(t_token **token, char *s, int start, int len);

//push_index_about_comma
int				count_space_out_of_comma(char *str);
void			push_index_until_space_or_oper(char *line, int *index);

//redirection
void			set_type_remove_operator(t_token **token, t_token **first);

//redirection2
char			*update_token_line(t_token **token);
void			sort_token_order(t_token **token, t_token **first, \
t_token *redir_token);

//check_subshell_redir
void			get_redir_token(t_token *tok);

//token_list_len
int				token_list_len(t_token *token);

//token_util
t_token			*ft_tokenstart(t_token *lst);
t_token			*ft_tokenlast(t_token *lst);
t_token			*new_token(t_info *info);

//tree_recursion
t_token			*get_tree(t_token *token);

//tree_check
void			viewtree(t_token *tok);
void			viewtree2(t_token *tok);
int				check_tree(t_token *token);

//tree_util
void			zero_parameter1(int *i, int *j, int *k);
void			zero_parameter(t_oper_type *i, t_oper_type *j, t_oper_type *k);
t_token			*next_token(t_token *token);
t_token			*prev_token(t_token *token);
void			select_oper(t_token *tok, t_oper_type *oper1, \
t_oper_type *oper2, t_oper_type *oper3);

//wildcard_dir
int				cnt_pwd(t_token *tok, char **pwd);
int				cnt_cmd(char **cmd);
int				check_wild(char *s);
DIR				*opendir_util(char *pwd, t_token *tok);

//wildcard
int				write_dir(struct dirent *file, DIR *dir_ptr, \
				char ***src, int i);
int				write_wild(char ***dst, char ***src, t_token *tok, char *pwd);
int				what_wild(char **new);
int				edit_wild(t_token *tok, int cnt, int *i);
int				free_wild(char *tmp, int ret);

//wildcard_com
char			*set_tok_cmd(t_token *tok, int i);
void			push_index_com(char *line, int *idx);
void			jump_redir(char *line, int *idx, int i);
char			*get_tok_cmd(t_token *tok, int idx);
int				com_wild(t_token *tok, int j);

//wildcard_arrs
int				is_wild(char *wild_str, char *file_name);
int				is_wildsub(char *wild_str, char *file_name, int index);
int				cnt_cwd_wild(t_token *tok, char *wild_str);
void			fill_arrs(t_token *tok, char *wild_str, char **arrs);
char			**make_arrs_with_wild(t_token *tok, char *wild_str);

//wildcard_utility
void			other_filling(t_token *tok, int *idx, char ***new, int j);
char			**filling_cmd(t_token *tok, int *idx, char **tmp, int cnt);
int				search_edit_wild(t_token *tok, int *i);
int				wild_type(t_token *tok, int *i);
int				expansion_wild(t_token *tok);

#endif