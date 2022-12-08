/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 20:49:37 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/07 23:50:01 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

void	ft_echo(char **cmd);
void	ft_cd(t_token *token);
void	ft_pwd(char **cmd);
void	ft_unset(t_token *token);
void	ft_export(t_token *token);
void	ft_env(t_token *token);

#endif