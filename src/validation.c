/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 15:59:01 by qle-guen          #+#    #+#             */
/*   Updated: 2016/02/22 14:01:27 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fillit.h>

int					valid_line
	(const char *line)
{
	char			*s;
	size_t			i;

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

void				shift_topleft
	(unsigned short *tetri)
{
	while (!(*tetri & 0xF))
		*tetri >>= 4;
	while (!(*tetri & 4369))
		*tetri >>= 1;
}

int					valid_tetri
	(unsigned short tetri)
{
	size_t			i;

	i = 0;
	while (i < sizeof(g_valid_tetris) / sizeof(g_valid_tetris[0]))
	{
		if (g_valid_tetris[i] == tetri)
			return (1);
		i++;
	}
	return (0);
}

void				count_lines_columns
	(t_tetri *tetri)
{
	unsigned short	value;
	char			max;

	value = tetri->value;
	tetri->lines = 0;
	tetri->columns = 0;
	max = 0;
	while (value)
	{
		if ((value & 0xF) > max)
			max = value & 0xF;
		tetri->lines++;
		value >>= 4;
	}
	while (max)
	{
		tetri->columns++;
		max >>= 1;
	}
}
