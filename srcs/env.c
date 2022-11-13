/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:53:13 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/13 20:21:33 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	init_env(t_info *info, char **envp)
{
	int			i;
	int			env_len;
	char 		**splited_env_arr;
	t_env_list	*tmp;

	env_len = get_sec_arr_len(envp);
	info->env_list = malloc(sizeof(t_env_list));
	if (!info->env_list)
		return (throw_error(MALLOC_ERR));
	tmp = info->env_list;
	ft_split_for_env(envp[0], &tmp->key, &tmp->value);
	tmp->next = NULL;
	i = 1;
	while (envp[i])
	{
		tmp->next = malloc(sizeof(t_env_list));
		if (!tmp->next)
			return (throw_error(MALLOC_ERR));
		tmp = tmp->next;
		ft_split_for_env(envp[i], &tmp->key, &tmp->value);
		tmp->next = NULL;
		i++;
	}
}

char *ft_getenv(t_env_list *env_list, char *key)
{
	t_env_list *tmp;

	tmp = env_list;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(key)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	printf_envs(t_env_list *env_list)
{
	while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}
