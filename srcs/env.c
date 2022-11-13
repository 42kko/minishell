/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:53:13 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/13 21:02:10 by seokchoi         ###   ########.fr       */
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

void	print_envs(t_env_list *env_list)
{
	while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}

void	ft_putenv(t_env_list *env_list, char *key, char *value)
{
	t_env_list	*tmp_a;
	t_env_list	*tmp_b;
	
	tmp_a = env_list;
	while (tmp_a)
	{
		if (!ft_strncmp(key, tmp_a->key, ft_strlen(key)))
		{
			free(tmp_a->value);
			tmp_a->value = ft_strdup(value);
			if (!tmp_a->value)
				throw_error(MALLOC_ERR);
			return ;
		}
		tmp_b = tmp_a;
		tmp_a = tmp_a->next;
	}
	tmp_b->next = malloc(sizeof(t_env_list));
	if (!tmp_b->next)
		throw_error(MALLOC_ERR);
	tmp_b->next->key = ft_strdup(key);
	tmp_b->next->value = ft_strdup(value);
	tmp_b->next->next = NULL;
}


void	ft_unset(t_env_list **env_list, char *key)
{
	t_env_list *tmp_a;
	t_env_list *tmp_b;

	tmp_a = *env_list;
	tmp_b = tmp_a;
	while (tmp_a)
	{
		if (!ft_strncmp(key, tmp_a->key, ft_strlen(key)))
		{
			if (tmp_a == *env_list)
			{
				*env_list = tmp_a->next;
				free_a_node_of_env_list(tmp_a);
				return ;
			}
			tmp_b->next = free_a_node_of_env_list(tmp_a);
			return ;
		}
		tmp_b = tmp_a;
		tmp_a = tmp_a->next;
	}
}