/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokchoi <seokchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:09:09 by seokchoi          #+#    #+#             */
/*   Updated: 2022/04/05 13:43:41 by seokchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print_number(int n, int fd)
{
	char	left;

	if (n > 9)
		ft_print_number(n / 10, fd);
	left = '0' + n % 10;
	write(fd, &left, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			n *= -1;
			write(fd, "-", 1);
		}
		ft_print_number(n, fd);
	}
}
