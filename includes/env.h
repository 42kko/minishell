/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:12:18 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/09 00:44:25 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef enum e_error_type	t_error_type;
typedef struct s_env_list	t_env_list;
typedef struct s_info		t_info;

struct s_info
{
	struct termios	*old_term;
	t_env_list		*env_list;
	char			**path;
	int				exit_num;
	int				stdio_backup[2];
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
	int			equal;
	char 		*value;
	t_env_list	*next;
};

// env
char 	*ft_getenv(t_env_list *env_list, char *key);
void	init_env(t_info *info, char **envp);
void	print_envs(t_env_list *env_list);
void	ft_putenv(t_env_list *env_list, char *key, char *value, int equal);
void	ft_unset_env_list(t_env_list **env_list, char *key);

// get
int	ft_split_for_env(char const *s, char **key, char **value);

// utility
int		get_sec_arr_len(char **arr);
void	free_sec_arr(char **arr);

// free
t_env_list	*free_a_node_of_env_list(t_env_list *env_list);

// env_arr
char		**get_env_arr(t_env_list *env_list);
char		**get_export_arr(t_env_list *env_list);
int			get_env_num(t_env_list *env_list);

// check_env
char			*change_key_to_value(char *cmd, t_keys *keys);
void			free_keys(t_keys *keys);


#endif