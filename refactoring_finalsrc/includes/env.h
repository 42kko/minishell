/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:12:18 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/08 11:17:47 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef enum e_error_type	t_error_type;
typedef struct s_change_tmp	t_change_tmp;

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
	char		*key;
	int			equal;
	char		*value;
	t_env_list	*next;
};

struct s_change_tmp
{
	int		i;
	int		k;
	int		j;
	int		ord;
	int		ch_idx;
};

// check_env
char		*change_key_to_value(char *cmd, t_keys *keys);
void		free_keys(t_keys *keys);

// env_arr
int			get_env_num(t_env_list *env_list);
char		**get_env_arr(t_env_list *env_list);

// env
void		init_env(t_info *info, char **envp);
char		*ft_getenv(t_env_list *env_list, char *key);
void		print_envs(t_env_list *env_list);
void		ft_putenv(t_env_list *env_list, char *key, char *value, int equal);

// free
t_env_list	*free_a_node_of_env_list(t_env_list *env_list);
void		free_env_list(t_env_list *env_list);

//ft_split_for_env
int			ft_split_for_env(char const *s, char **key, char **value);
int			is_dont_be_key(char *key);

//ft_unset_env_list
void		ft_unset_env_list(t_env_list **env_list, char *key);

//ft_unset_env_list
void		ft_unset_env_list(t_env_list **env_list, char *key);

#endif