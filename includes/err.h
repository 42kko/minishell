/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:17:36 by kko               #+#    #+#             */
/*   Updated: 2022/12/10 01:52:16 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

//err
void	throw_error_syntax(t_error_type type, t_token *tok);
void	err_msg(char *msg, t_token *tok, char *target);
void	throw_error_message(char *cmd, char *err, \
char *message, int exit_errno);
void	throw_error(t_error_type type);

//err_msg_syntax_int
int		err_msg_syntax_int(t_info *info);

#endif