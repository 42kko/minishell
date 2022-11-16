/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:25:03 by seokchoi          #+#    #+#             */
/*   Updated: 2022/11/16 21:26:38 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum e_oper_type	t_oper_type;
typedef enum e_comma_type	t_comma_type;

enum e_oper_type
{
	NO_TYPE,
	TCMD,
	TOUT, //>
	TADDOUT, //>>
	TIN, //<
	TDOC, //<<
	TPIPE, //|
	TOR, //||
	TAND, //&
	TDAND, //&&
	TSEMI, //;
};

enum e_comma_type
{
	NO_COM,
	ONE_COM,
	TWO_COM,
};

typedef struct s_token
{
	t_oper_type			type;
	char				**cmd;
	t_comma_type		comma_type;
	char				*line;
	struct s_token		*next;
}	t_token;

t_token	*ft_tokenlast(t_token *lst);

#endif