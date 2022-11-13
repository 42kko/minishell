/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:24:01 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/13 14:26:24 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include "libft.h"

typedef enum e_error_type	t_error_type;
typedef struct s_info		t_info;
typedef struct s_env		t_env;

enum e_error_type
{
	ATOI_ERR = -1,
	NO_ERR,
	MALLOC_ERR,
};

typedef struct s_env
{
	char **envs;
	int	env_num;
};

typedef struct s_env_list
{
	char 		*key;
	char 		value;
	t_env_list	*next;
}	t_env_list;

typedef struct s_info
{
	t_env *env;
};

// env
char 	*ft_getenv(t_env *env, char *key);
void	init_env(t_info *info, char **envp);

// get
char	**ft_split_for_env(char const *s);

#endif