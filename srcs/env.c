/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:53:13 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/11 20:28:32 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	get_sec_arr_len(const char **arr)
{
	int	length;

	length = 0;
	while (arr[length])
		length++;
	return (length);
}

void	init_env(t_info *info, char **envp)
{
	int		i;

	info->env = malloc(sizeof(t_env));
	if (info->env)
		throw_error(MALLOC_ERR);
	info->env->env_num = get_sec_arr_len(envp);
	info->env->envs = (char **)malloc(sizeof(char *) * info->env->env_num);
	if (info->env->envs)
		throw_error(MALLOC_ERR);
	i = 0;
	while (i < info->env->env_num)
	{
		info->env->envs[i] = (char *)malloc(sizeof(char) * ft_strlen(envp[i]));
		if (info->env->envs[i])
			throw_error(MALLOC_ERR);
		i++;
	}
}

void	free_sec_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char *ft_getenv(t_env *env, char *key)
{
	int		i;
	char	**strs;
	char	*value;

	i = 0;
	while (i < env->env_num)
	{
		strs = ft_split(env->envs[i], '=');
		if (!strs)
			throw_error(MALLOC_ERR);
		if (get_sec_arr_len(strs) > 0)
		{
			if (ft_strncmp(key, strs[0], ft_strlen(strs[0])) == 0)
			{
				
				break ;
			}
		}
		free_sec_arr(strs);
		i++;
	}
	return ();
}
