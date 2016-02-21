/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 03:30:23 by qle-guen          #+#    #+#             */
/*   Updated: 2016/01/26 03:54:31 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fillit.h>

int			ft_sqrt(int x)
{
	int		n;

	n = 0;
	while (n * n < x)
		n++;
	return (n);
}
