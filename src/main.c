/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 07:49:23 by qle-guen          #+#    #+#             */
/*   Updated: 2016/01/26 03:55:02 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fillit.h>


int			valid_line(const char *line)
{
	char		*s;
	size_t		i;

	if (!line)
		return (0);
	s = (char *)line;
	i = 0;
	while (i < 20)
	{
		if ((((i + 1) % 5) == 0 && s[i] == '\n')
			|| ((s[i] == '#' || s[i] == '.')))
			i++;
		else
			return (0);
	}
	return (1);
}

void		shift_topleft(t_tetri *tetri)
{
	while (!(*tetri & 0xF))
		*tetri >>= 4;
	while (!(*tetri & 4369))
		*tetri >>= 1;
}

int			valid_tetri(t_tetri tetri)
{
	size_t	i;
	t_tetri	valid_tetris[] = {
		15, 16, 23, 39, 51, 54, 71, 99, 113, 114, 116,
		275, 305, 306, 547, 561, 562, 785, 802, 4369};
	i = 0;
	while (i < sizeof(valid_tetris)/sizeof(valid_tetris[0]))
	{
		if (valid_tetris[i] == tetri)
			return (1);
		i++;
	}
	return (0);
}

int			read_tetri(int fd, t_list **tetris)
{
	size_t	i;
	t_tetri	*tetri;
	char	line[21];
	char	*buf;
	int		r_result;

	tetri = ft_memalloc(sizeof(*tetri));
	ft_bzero(line, 21);
	r_result = read(fd, line, 21);
	if (r_result == -1 || !valid_line(line))
		return (-1);
	line[20] = '\0'; 
	while ((buf = ft_strchr(line, '#')))
	{
		i = buf - line - 4;
		*buf = '.';
		while ((buf = ft_strchr(buf, '\n')) && buf++)
			i++;
		*tetri |= 1 << i;
	}
	shift_topleft(tetri);
	if (!valid_tetri(*tetri))
		return (-1);
	ft_lstpush(tetris, tetri, sizeof(*tetri));
	return (r_result == 21);
}

int			main(int argc, char **argv)
{
	int		fd;
	int		result;
	int		width;
	t_list	*tetris;
	t_list	*boards;

	tetris = NULL;
	if (argc != 2 || (fd = open(argv[1], O_RDONLY, 0)) == -1)
	{
		ft_putendl("error");
		return (1);
	}
	while (1)
	{
		result = read_tetri(fd, &tetris);
		if (!result)
			break;
		if (result == -1)
		{
			ft_putendl("error");
			return (1);
		}
	}
	width = main_loop(ft_sqrt(ft_lstsize(tetris) * 4), tetris, &boards);
	print_final_board(boards, width);
}
