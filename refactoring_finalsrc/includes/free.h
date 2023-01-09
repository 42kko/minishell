/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 01:36:55 by seokchoi          #+#    #+#             */
/*   Updated: 2022/12/10 01:59:38 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

//free
void	free_cmd(char **cmd);
int		free_lst(t_token *tok, t_info *info);
void	free_tree(t_token *tok);

//utility
void	free_sec_arr(char **arr);
int		get_sec_arr_len(char **arr);

#endif