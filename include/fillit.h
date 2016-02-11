/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 07:54:19 by qle-guen          #+#    #+#             */
/*   Updated: 2016/02/11 18:29:27 by qle-guen         ###   ########.fr       */
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

void				print_final_board(t_list *boards, size_t w);
int					try_width(t_list *boards, size_t w, t_list *tetris, size_t offset);
int					main_loop(size_t starting_width, t_list *tetris, t_list **sol);
int					ft_sqrt(int x);
void				ft_exit(char *msg, int status);

#endif
