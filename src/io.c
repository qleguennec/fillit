/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 06:25:24 by qle-guen          #+#    #+#             */
/*   Updated: 2016/01/26 11:11:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fillit.h>

void			print_square(t_square *square)
{
	size_t		i;

	i = 0;
	while (i < square->width * square->width)
	{
		if (!(((t_board)1 << i) & *square->board))
			ft_putchar('.');
		else
			ft_putchar('#');
		if (!((i + 1) % square->width))
			ft_putchar('\n');
		i++;
	}
}

void			print_tetri(t_list *tetri)
{
	t_square	*square;

	square = ft_memalloc(sizeof(*square));
	square->board = ft_memalloc(sizeof(*square->board));
	ft_memcpy(square->board, (t_tetri *)tetri->content, tetri->content_size);
	square->width = 4;
	print_square(square);
	if (tetri->next)
		ft_putchar('\n');
}

void			print_binary(unsigned long a, size_t space)
{
	size_t		i;
	char		buffer[sizeof(a) * 9 + 12];

	i = 0;
	ft_bzero(buffer, sizeof(buffer));
	while (i < sizeof(a) * 8)
	{
		strcat(buffer, ft_itoa(1 & a));
		if ((i + 1) % space == 0)
		{
			strcat(buffer, "\t");
			if (!a)
			{
				strcat(buffer, ft_strrev(ft_itoa(sizeof(a) * 8 - i)));
				break;
			}
		}
		a >>= 1;
		i++;
	}
	ft_putendl(ft_strrev(buffer));
}

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
