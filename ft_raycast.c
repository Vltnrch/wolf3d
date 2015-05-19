/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 11:51:07 by vroche            #+#    #+#             */
/*   Updated: 2015/05/19 12:02:20 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** All raycasting fonction for wolf3d
** init all camera and rayon position
** check ray direction
** check wall presence and distance
** calc init and end draw point
*/

#include "wolf3d.h"

void	ft_init_calc(t_env *env, t_w3d *w3d)
{
	w3d->camerax = 2 * env->xi / (double)LENGHT - 1;
	w3d->rayposx = w3d->posx;
	w3d->rayposy = w3d->posy;
	w3d->raydirx = w3d->dirx + w3d->planex * w3d->camerax;
	w3d->raydiry = w3d->diry + w3d->planey * w3d->camerax;
	w3d->mapx = (int)w3d->rayposx;
	w3d->mapy = (int)w3d->rayposy;
	w3d->deltadistx = sqrt(1 + (w3d->raydiry * w3d->raydiry) \
					/ (w3d->raydirx * w3d->raydirx));
	w3d->deltadisty = sqrt(1 + (w3d->raydirx * w3d->raydirx) \
					/ (w3d->raydiry * w3d->raydiry));
	w3d->hit = 0;
}

void	ft_wolf_raydir(t_w3d *w3d)
{
	if (w3d->raydirx < 0)
	{
		w3d->stepx = -1;
		w3d->sidedistx = (w3d->rayposx - w3d->mapx) * w3d->deltadistx;
	}
	else
	{
		w3d->stepx = 1;
		w3d->sidedistx = (w3d->mapx + 1.0 - w3d->rayposx) * w3d->deltadistx;
	}
	if (w3d->raydiry < 0)
	{
		w3d->stepy = -1;
		w3d->sidedisty = (w3d->rayposy - w3d->mapy) * w3d->deltadisty;
	}
	else
	{
		w3d->stepy = 1;
		w3d->sidedisty = (w3d->mapy + 1.0 - w3d->rayposy) * w3d->deltadisty;
	}
}

void	ft_wolf_walldistance(t_w3d *w3d)
{
	while (w3d->hit == 0)
	{
		if (w3d->sidedistx < w3d->sidedisty)
		{
			w3d->sidedistx += w3d->deltadistx;
			w3d->mapx += w3d->stepx;
			w3d->side = 0;
		}
		else
		{
			w3d->sidedisty += w3d->deltadisty;
			w3d->mapy += w3d->stepy;
			w3d->side = 1;
		}
		if (w3d->worldmap[w3d->mapx][w3d->mapy] > 0)
			w3d->hit = 1;
	}
	if (w3d->side == 0)
		w3d->perpwalldist = fabs((w3d->mapx - w3d->rayposx \
								+ (1 - w3d->stepx) / 2) / w3d->raydirx);
	else
		w3d->perpwalldist = fabs((w3d->mapy - w3d->rayposy \
								+ (1 - w3d->stepy) / 2) / w3d->raydiry);
	w3d->lineheight = abs((int)(HEIGHT / w3d->perpwalldist));
}

void	ft_wolf_calcdraw(t_env *env, t_w3d *w3d)
{
	env->yi = -w3d->lineheight / 2 + HEIGHT / 2;
	if (env->yi < 0)
		env->yi = 0;
	env->yf = w3d->lineheight / 2 + HEIGHT / 2;
	if (env->yf >= HEIGHT)
		env->yf = HEIGHT - 1;
}
