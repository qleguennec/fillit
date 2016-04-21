/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 06:25:24 by qle-guen          #+#    #+#             */
/*   Updated: 2016/04/21 15:40:25 by qle-guen         ###   ########.fr       */
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

void		ft_exit(char *msg, int status)
{
	ft_putendl(msg);
	exit(status);
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
	if ((r_result = read(fd, line, 21)) == -1 || !valid_line(line)
		|| !ft_strchr(line, '#'))
		return (-1);
	line[20] = '\0';
	while ((buf = ft_strchr(line, '#')) && (*buf = '.'))
	{
		i = buf - line - 4;
		while ((buf = ft_strchr(buf, '\n')) && buf++)
			i++;
		tetri->value |= 1 << i;
	}
	shift_topleft(&tetri->value);
	if (!valid_tetri(tetri->value))
		return (-1);
	count_lines_columns(tetri);
	ft_lstpush(tetris, tetri, sizeof(*tetri));
	return (r_result == 21);
}
