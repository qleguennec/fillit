/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 07:54:19 by qle-guen          #+#    #+#             */
/*   Updated: 2016/02/22 14:01:03 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define BOARDTYPE unsigned __int128

# include <unistd.h>
# include <libft.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef	BOARDTYPE			t_board;

typedef struct				s_tetri
{
	unsigned short			value;
	char					lines;
	char					columns;
}							t_tetri;

typedef struct				s_play_result
{
	t_board					new_board;
	size_t					new_offset;
}							t_play_result;

static unsigned short		g_valid_tetris[] =
{
	15, 23, 39, 51, 54, 71, 99, 113, 114
	, 116, 275, 305, 306, 547, 561, 562, 785, 802, 4369
};

void						print_final_board
	(t_list *boards, size_t w);
int							main_loop
	(size_t starting_width, t_list *tetris, t_list **sol);
int							ft_sqrt(int x);
void						ft_exit(char *msg, int status);
int							read_tetri(int fd, t_list **tetris);
int							valid_line(const char *line);
void						shift_topleft(unsigned short *value);
int							valid_tetri(unsigned short value);
void						count_lines_columns(t_tetri *tetri);
void						ft_boardclr(t_list *l);

#endif
