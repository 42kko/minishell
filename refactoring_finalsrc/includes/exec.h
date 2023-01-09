/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihonkim <gidrlantk@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:17:36 by kko               #+#    #+#             */
/*   Updated: 2023/01/03 15:09:40 by jihonkim         ###   ########.fr       */
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
int		ft_builitin(t_token *tok);
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

//open_redir_util
int		get_index_redir(char *tmp, int i);
char	*get_prev_line(t_token *tok, t_token *first, int idx);
int		com_wild_redir(char *tmp);
char	*ft_redir(char *s);
void	change_lien(t_token *tok, char **tmp1);

//open_redir_wild
void	edit_wild_redir(t_token *tok, t_token *first, int idx);
void	expansion_wild_redir(t_token *tok, t_token *first);

//open_util
char	*find_redir(char *s);
void	close_util(int fd, t_token *tok);
int		fork_util(t_token *tok);

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