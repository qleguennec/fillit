/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 07:06:27 by qle-guen          #+#    #+#             */
/*   Updated: 2016/02/11 14:12:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fillit.h>

int				valid_play(t_board *b, size_t w, t_tetri t, size_t offset)
{
	unsigned char	stat[3];
	t_tetri			old_t;

	if (offset > w * w)
		return (-1);
	ft_bzero(stat, sizeof(stat));
	old_t = t;
	while (t)
	{
		if (stat[0] + offset / w >= w)
			return (-1);
		if (*b & (t_board)(t & 0xF) << (w * stat[0] + offset))
			return (valid_play(b, w, old_t, offset + 1));
		if ((t & 0xF) > stat[2])
			stat[2] = t & 0xF;
		t >>= 4;
		stat[0]++;
	}
	while (stat[2])
	{
		stat[2] >>= 1;
		if (stat[1] + offset % w >= w)
			return (valid_play(b, w, old_t, offset + 1));
	}
	return (offset);
}

t_board			*play(t_board *b, size_t w, t_tetri t, size_t offset)
{
	size_t		i;
	size_t		new_offset;
	t_board		*new_board;

	i = 0;
	new_board = ft_memalloc(sizeof(*new_board));
	*new_board = *b;
	if ((new_offset = valid_play(b, w, t, offset)) == -1)
		return (NULL);
	while (t)
	{
		*new_board |= (t_board)(t & 0xF)
			<< (w * i + new_offset);
		t >>= 4;
		i++;
	}
	return (new_board);
}

int				try_width
	(t_list *boards, size_t w, t_list *tetris, size_t offset)
{
	t_board	*new_board;

	if (!tetris)
		return (1);
	new_board = play(boards->content, w, *((t_tetri *)tetris->content), offset);
	if (new_board)
	{
		boards->next = ft_lstnew(new_board, sizeof(*new_board));
		if (try_width(boards->next, w, tetris->next, 0))
			return (1);
		else
		{
			ft_lstdel(&boards->next, &ft_delete);
			return (try_width(boards, w, tetris, offset + 1));
		}
	}
	return (0);
}

int				main_loop(size_t starting_width, t_list *tetris, t_list **sol)
{
	size_t	width;
	t_list	*board;

	width = starting_width;
	board = ft_lstnew(ft_memalloc(sizeof(t_board)), sizeof(t_board));
	while (!try_width(board, width, tetris, 0))
	{
		ft_lstdel(&board->next, &ft_delete);
		width++;
	}
	*sol = board;
	return (width);
}
