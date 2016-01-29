/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 07:54:19 by qle-guen          #+#    #+#             */
/*   Updated: 2016/01/26 03:34:08 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include <unistd.h>
#include <stdio.h>
#include <libft.h>
#include <fcntl.h>
#include <stdlib.h>

typedef unsigned short t_tetri;
typedef unsigned __int128 t_board;

typedef struct		s_state
{
	t_list			*tetris;
	int				debug;
	int				fd;
}					t_state;

typedef struct		s_square
{
	t_board			*board;
	size_t			width;
}					t_square;

void				print_tetri(t_list *tetri);
void				print_square(t_square *square);
void				print_final_board(t_list *boards, size_t w);
void				print_binary(unsigned long a, size_t space);
int					try_width(t_list *boards, size_t w, t_list *tetris, size_t offset);
int					main_loop(size_t starting_width, t_list *tetris, t_list **sol);
int					ft_sqrt(int x);

#endif
