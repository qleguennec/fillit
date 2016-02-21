/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 07:49:23 by qle-guen          #+#    #+#             */
/*   Updated: 2016/02/21 17:46:00 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fillit.h>

int			main
	(int argc, char **argv)
{
	int		fd;
	int		result;
	int		width;
	t_list	*tetris;
	t_list	*boards;

	tetris = NULL;
	if (argc != 2)
		ft_exit("usage: fillit file", 1);
	if ((fd = open(argv[1], O_RDONLY, 0)) == -1)
		ft_exit("error", 1);
	while (1)
	{
		result = read_tetri(fd, &tetris);
		if (!result)
			break ;
		if (result == -1)
			ft_exit("error", 1);
	}
	width = main_loop(ft_sqrt(ft_lstsize(tetris) * 4), tetris, &boards);
	print_final_board(boards, width);
	return (0);
}
