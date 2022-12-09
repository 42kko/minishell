/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:17:36 by kko               #+#    #+#             */
/*   Updated: 2022/12/09 01:36:41 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_pipe
{
	int	cnt;
	int	*p;
}	t_pipe;

//built_run
int		ft_bulitin(t_token *tok);
void	built_exec(t_token *tok);
void	builtin_alone_exec(t_token *tok);

//exec
int		identify_built_exec(t_token *tok);
void	exec(t_token *tok);

//here_doc
int		here_doc(char *limiter, t_token *tok);

//ioctl
void	io_ctl_cmd(t_token *tok);
void	io_ctl(t_pipe *pip, int i, t_token *tok);

//oepn_redir
void	open_redir(t_token *tok);

//open_util
char	*find_redir(char *s);
void	close_util(int fd, t_token *tok);

//path
char	**info_get_path(t_info *info);
void	add_path(t_token *tok);

//pipe_util
void	new_pipe(t_pipe *pip);
int		cnt_pipe(t_token **tok);

//run_pipe
void	run_pipe(t_token *tok);

//run
void	run_shell(t_token *tok);

#endif