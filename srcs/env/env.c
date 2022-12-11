/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:53:13 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/11 21:33:01 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_env_wave(t_info *info)
{
	char		*home_path;

	home_path = ft_getenv(info->env_list, "HOME");
	ft_putenv(info->env_list, "~", home_path, 0);
	free(home_path);
}

void	init_env(t_info *info, char **envp)
{
	int			i;
	int			env_len;
	t_env_list	*tmp;

	env_len = get_sec_arr_len(envp);
	info->env_list = ft_calloc(sizeof(t_env_list), 1);
	if (!info->env_list)
		return (throw_error(MALLOC_ERR));
	tmp = info->env_list;
	ft_split_for_env(envp[0], &tmp->key, &tmp->value);
	tmp->next = NULL;
	i = 1;
	while (envp[i])
	{
		tmp->next = ft_calloc(sizeof(t_env_list), 1);
		if (!tmp->next)
			return (throw_error(MALLOC_ERR));
		tmp = tmp->next;
		ft_split_for_env(envp[i], &tmp->key, &tmp->value);
		tmp->next = NULL;
		i++;
	}
	set_env_wave(info);
}

char	*ft_getenv(t_env_list *env_list, char *key)
{
	t_env_list	*tmp;
	char		*fail;
	char		*value;

	tmp = env_list;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(key) + 1))
		{
			value = ft_strdup(tmp->value);
			if (!value)
				throw_error(MALLOC_ERR);
			return (value);
		}
		tmp = tmp->next;
	}
	fail = ft_strdup("");
	if (!fail)
		throw_error(MALLOC_ERR);
	return (fail);
}

void	print_envs(t_env_list *env_list)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->key, "~", 2) != 0 && env_list->equal == 0)
			printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}

void	ft_putenv(t_env_list *env_list, char *key, char *value, int equal)
{
	t_env_list	*tmp_a;
	t_env_list	*tmp_b;

	tmp_a = env_list;
	while (tmp_a)
	{
		if (!ft_strncmp(key, tmp_a->key, ft_strlen(key) + 1))
		{
			free(tmp_a->value);
			tmp_a->value = ft_strdup(value);
			tmp_a->equal = equal;
			if (!tmp_a->value)
				throw_error(MALLOC_ERR);
			return ;
		}
		tmp_b = tmp_a;
		tmp_a = tmp_a->next;
	}
	tmp_b->next = ft_calloc(sizeof(t_env_list), 1);
	if (!tmp_b->next)
		throw_error(MALLOC_ERR);
	tmp_b->next->key = ft_strdup(key);
	tmp_b->next->value = ft_strdup(value);
	tmp_b->next->next = NULL;
	tmp_b->next->equal = equal;
}
