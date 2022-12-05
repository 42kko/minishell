/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ko <ko@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:12:18 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/05 20:40:37 by ko               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

typedef enum e_error_type	t_error_type;
typedef struct s_env_list	t_env_list;
typedef struct s_info		t_info;

struct s_info
{
	t_env_list *env_list;
};

enum e_error_type
{
	NO_ERR,
	MALLOC_ERR,
	SYNTAX_ERR,
	SYNTAX_ERR_TREE,
	FORK_ERR,
	COMMAND_NOT,
};

struct s_env_list
{
	char 		*key;
	char 		*value;
	t_env_list	*next;
};

// env
char 	*ft_getenv(t_env_list *env_list, char *key);
void	init_env(t_info *info, char **envp);
void	print_envs(t_env_list *env_list);
void	ft_putenv(t_env_list *env_list, char *key, char *value);
void	ft_unset(t_env_list **env_list, char *key);

// get
void	ft_split_for_env(char const *s, char **key, char **value);

// throw_error
void	throw_error(t_error_type type);

// utility
int		get_sec_arr_len(char **arr);
void	free_sec_arr(char **arr);

// free
t_env_list	*free_a_node_of_env_list(t_env_list *env_list);
