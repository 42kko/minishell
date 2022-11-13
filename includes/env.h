/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:12:18 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/13 21:02:25 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_error_type	t_error_type;
typedef struct s_info		t_info;
typedef struct s_env_list	t_env_list;

enum e_error_type
{
	ATOI_ERR = -1,
	NO_ERR,
	MALLOC_ERR,
};
struct s_env_list
{
	char 		*key;
	char 		*value;
	t_env_list	*next;
};

struct s_info
{
	t_env_list *env_list;
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
