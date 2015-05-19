/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 11:51:07 by vroche            #+#    #+#             */
/*   Updated: 2015/05/19 12:02:06 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_minimap draw minimap
** draw black front
** draw square for every wall
** draw red point about camera position
*/

#include "wolf3d.h"

static void	ft_minimap_point(t_env *env, t_w3d *w3d)
{
	int	x;
	int	y;

	x = w3d->posy * 181 / MAPWIDTH;
	y = w3d->posx * 181 / MAPHEIGHT;
	ft_put_pixel_to_image(0xff0000, env, x - 1, y - 1);
	ft_put_pixel_to_image(0xff0000, env, x - 1, y + 1);
	ft_put_pixel_to_image(0xff0000, env, x + 1, y - 1);
	ft_put_pixel_to_image(0xff0000, env, x + 1, y + 1);
	ft_put_pixel_to_image(0xff0000, env, x + 1, y);
	ft_put_pixel_to_image(0xff0000, env, x, y + 1);
	ft_put_pixel_to_image(0xff0000, env, x, y - 1);
	ft_put_pixel_to_image(0xff0000, env, x - 1, y);
	ft_put_pixel_to_image(0xff0000, env, x, y);
	ft_put_pixel_to_image(0xff0000, env, x + 2, y);
	ft_put_pixel_to_image(0xff0000, env, x, y + 2);
	ft_put_pixel_to_image(0xff0000, env, x, y - 2);
	ft_put_pixel_to_image(0xff0000, env, x - 2, y);
}

static void	ft_drawall_minimap(t_env *env, t_w3d *w3d, int mw)
{
	int	mh;

	mh = 0;
	while (mh < MAPHEIGHT)
	{
		if (w3d->worldmap[mw][mh] != 0)
		{
			env->xi = 6 * mh + 1;
			env->yi = 6 * mw + 1;
			env->xf = env->xi + 4;
			env->yf = env->yi;
			while (env->yi <= 6 * mw + 5)
			{
				if (w3d->worldmap[mw][mh] <= 2)
					ft_draw_line(env, 0xffffff);
				else
					ft_draw_line(env, 0x0000ff);
				env->yf++;
				env->yi++;
			}
		}
		mh++;
	}
}

void		ft_minimap(t_env *env, t_w3d *w3d)
{
	int	mw;

	env->xi = 0;
	env->yi = 0;
	env->xf = 181;
	env->yf = 0;
	while (env->yf <= 181)
	{
		ft_draw_line(env, 0x000000);
		env->yf++;
		env->yi++;
	}
	mw = 0;
	while (mw < MAPWIDTH)
		ft_drawall_minimap(env, w3d, mw++);
	ft_minimap_point(env, w3d);
}
