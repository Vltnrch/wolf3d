/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 11:51:07 by vroche            #+#    #+#             */
/*   Updated: 2015/05/19 11:59:39 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Bresenham algorith segment
** see draw  struct for see variables
** adapted here for wolf3d
*/

#include "wolf3d.h"

static void	draw_init(t_env *env, t_draw *draw)
{
	draw->x = env->xi;
	draw->y = env->yi;
	draw->dx = env->xf - env->xi;
	draw->dy = env->yf - env->yi;
	draw->xinc = (draw->dx > 0) ? 1 : -1;
	draw->yinc = (draw->dy > 0) ? 1 : -1;
	draw->dx = abs(draw->dx);
	draw->dy = abs(draw->dy);
}

static void	draw_sup(t_draw *draw, t_env *env, int color)
{
	draw->cumul = draw->dx / 2;
	draw->i = 1;
	while (draw->i <= draw->dx)
	{
		draw->x += draw->xinc;
		draw->cumul += draw->dy;
		if (draw->cumul >= draw->dx)
		{
			draw->cumul -= draw->dx;
			draw->y += draw->yinc;
		}
		ft_put_pixel_to_image(color, env, draw->x, draw->y);
		(draw->i)++;
	}
}

static void	draw_inf(t_draw *draw, t_env *env, int color)
{
	draw->cumul = draw->dy / 2;
	draw->i = 1;
	while (draw->i <= draw->dy)
	{
		draw->y += draw->yinc;
		draw->cumul += draw->dx;
		if (draw->cumul >= draw->dy)
		{
			draw->cumul -= draw->dy;
			draw->x += draw->xinc;
		}
		ft_put_pixel_to_image(color, env, draw->x, draw->y);
		(draw->i)++;
	}
}

void		ft_draw_line(t_env *env, int color)
{
	t_draw	draw;

	draw_init(env, &draw);
	ft_put_pixel_to_image(color, env, draw.x, draw.y);
	if (draw.dx > draw.dy)
		draw_sup(&draw, env, color);
	else
		draw_inf(&draw, env, color);
}
