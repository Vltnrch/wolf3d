/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_teleport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 11:51:07 by vroche            #+#    #+#             */
/*   Updated: 2015/05/19 12:02:29 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** fonction who search another teleport block and place camera position on it
*/

#include "wolf3d.h"

void	ft_teleport(t_w3d *w3d, int search)
{
	int	posx;
	int	posy;
	int	x;
	int	y;

	posx = (int)w3d->posx;
	posy = (int)w3d->posy;
	x = 0;
	while (x < MAPWIDTH)
	{
		y = 0;
		while (y < MAPHEIGHT)
		{
			if (x != posx && y != posy && w3d->worldmap[x][y] == search)
			{
				w3d->posx = 0.5f + x;
				w3d->posy = 0.5f + y;
				return ;
			}
			y++;
		}
		x++;
	}
}
