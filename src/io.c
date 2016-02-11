/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 06:25:24 by qle-guen          #+#    #+#             */
/*   Updated: 2016/02/11 12:04:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fillit.h>

void		print_final_board(t_list *boards, size_t w)
{
	char	*s;
	size_t	i;
	size_t	lstsize;

	s = ft_strnew(w * w);
	ft_memset(s, '.', w * w);
	lstsize = ft_lstsize(boards);
	while (boards)
	{
		i = 0;
		while (*((t_board *)boards->content))
		{
			if (*((t_board *)boards->content) & 1 && s[i] == '.')
				s[i] = 'A' + lstsize - ft_lstsize(boards) - 1;
			i++;
			*((t_board *)boards->content) >>= 1;
		}
		boards = boards->next;
	}
	while (*s)
	{
		write(1, s, w);
		ft_putchar('\n');
		s += w;
	}
}
