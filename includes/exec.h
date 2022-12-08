/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kko <kko@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:17:36 by kko               #+#    #+#             */
/*   Updated: 2022/12/08 23:58:48 by kko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_pipe
{
	int	cnt;
	int	*p;
}	t_pipe;

void	run_shell(t_token *tok);
void	run_subshell(t_token *tok);
void	run_exec(t_token *tok);
void	exec(t_token *tok);

#endif