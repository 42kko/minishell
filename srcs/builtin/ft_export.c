/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:33:15 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/12 20:33:06 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	compare_str(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] - s2[i] < 0)
			return (1);
		else if (s1[i] - s2[i] > 0)
			return (0);
		i++;
	}
	if (s1[i] == '\0')
		return (1);
	else
		return (0);
}

static void	sort_env(char **env, int env_len)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (env[i] && i < env_len - 1)
	{
		j = i + 1;
		while (env[j] && j < env_len)
		{
			if (compare_str(env[i], env[j]) == 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		printf("declare -x ");
		printf("%s\n", cmd[i]);
		i++;
	}
}

static void	check_export_arg_right(t_token *token)
{
	char	*key;
	char	*value;
	int		flag;
	int		i;

	i = 1;
	while (token->cmd[i])
	{
		flag = ft_split_for_env(token->cmd[i], &key, &value);
		if (flag == FAIL)
		{
			token->info->exit_num = 1;
			throw_error_message("export", token->cmd[i], \
			"not a valid identifier", 1);
		}
		else
			check_export_util(token, &flag, &key, &value);
		free(key);
		free(value);
		i++;
	}
}

void	ft_export(t_token *token)
{
	t_env_list	*env_list;
	int			cmd_len;
	char		**env;

	cmd_len = get_sec_arr_len(token->cmd);
	env_list = token->info->env_list;
	if (cmd_len == 1)
	{
		env = get_export_arr(env_list);
		sort_env(env, get_env_num(env_list));
		print_export(env);
		free_sec_arr(env);
		token->info->exit_num = 0;
		return ;
	}
	if (token->cmd[1])
		check_export_arg_right(token);
}
