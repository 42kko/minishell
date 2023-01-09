/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 20:49:37 by seokchoi          #+#    #+#             */
/*   Updated: 2023/01/08 11:15:49 by jihonkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

void	ft_echo(char **cmd, t_token *token);
void	ft_cd(t_token *token);
void	ft_pwd(char **cmd);
void	ft_unset(t_token *token);
void	ft_export(t_token *token);
void	check_export_util(t_token *token, int *flag, \
char **key, char **value);
void	ft_env(t_token *token);
void	ft_exit_with_print(t_token *tok, char **cmd, \
int number, int err_code);
void	ft_exit(t_token *tok, char **cmd);
char	**get_export_arr(t_env_list *env_list);

#endif