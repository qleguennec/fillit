/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 07:06:27 by qle-guen          #+#    #+#             */
/*   Updated: 2016/02/21 16:57:05 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fillit.h>

int					valid_play
	(t_board *b, size_t w, t_tetri t, size_t offset)
{
	unsigned short	value;
	size_t			i;

	while (1)
	{
		if ((offset > w * w)
			|| (t.lines + offset / w > w))
			return (-1);
		if (t.columns + offset % w <= w)
		{
			i = 0;
			value = t.value;
			while (value)
			{
				if (*b & (t_board)(value & 0xF) << (w * i + offset))
					break;
				value >>= 4;
				i++;
			}
			if (!value)
				return (offset);
		}
		offset++;
	}
}

static t_play_result		*play
	(t_board *b, size_t w, t_tetri t, size_t offset)
{
	t_play_result			*play_result;
	size_t					i;
	size_t					new_offset;

	if ((new_offset = valid_play(b, w, t, offset)) == -1)
		return (NULL);
	play_result = malloc(sizeof(*play_result));
	play_result->new_board = *b;
	i = 0;
	while (t.value)
	{
		play_result->new_board
			|= (t_board)(t.value & 0xF) << (w * i + new_offset);
		t.value >>= 4;
		i++;
	}
	play_result->new_offset = new_offset;
	return (play_result);
}

static int					try_width
	(t_list *boards, size_t w, t_list *tetris, size_t offset)
{
	t_play_result			*play_result;
	t_board					new_board;
	t_tetri					t;

	if (!tetris)
		return (1);
	t = *(t_tetri *)tetris->content;
	play_result = play(boards->content, w, t, offset);
	if (play_result)
	{
		new_board = play_result->new_board;
		if (!boards->next)
			boards->next = ft_lstnew(&new_board, sizeof(new_board));
		else
			(*(t_board *)boards->next->content) = new_board;
		if (try_width(boards->next, w, tetris->next, 0))
			return (1);
		else
		{
			ft_lstiter(boards->next, &ft_boardclr);
			return (try_width(boards, w, tetris,
				play_result->new_offset + 1));
		}
	}
	return (0);
}

int					main_loop
	(size_t starting_width, t_list *tetris, t_list **sol)
{
	size_t		width;
	t_list		*board;

	width = starting_width;
	board = ft_lstnew(ft_memalloc(sizeof(t_board)), sizeof(t_board));
	while (!try_width(board, width, tetris, 0))
	{
		ft_lstiter(board->next, &ft_boardclr);
		width++;
	}
	*sol = board;
	return (width);
}
