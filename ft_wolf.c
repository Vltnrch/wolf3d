/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wolf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 11:51:07 by vroche            #+#    #+#             */
/*   Updated: 2015/05/19 12:03:45 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_wolf execute all raycasting algorithm
** ft_init wolf draw sky and front
** ft_wolf_wallcolor select wall color fonction of direction
*/

#include "wolf3d.h"

static void	ft_init_wolf(t_env *env)
{
	int		i;
	char	*data;
	char	*sky;

	i = 0;
	env->xi = 0;
	env->yi = 384;
	env->xf = LENGHT;
	data = env->data;
	sky = env->sky;
	while (i < 2 * env->hsky * env->wsky)
	{
		*data++ = *sky++;
		i++;
	}
	while (env->yi < HEIGHT)
	{
		env->yf = env->yi;
		ft_draw_line(env, 0x7e8082);
		env->yi++;
	}
}

static void	ft_wolf_wallcolor(t_w3d *w3d)
{
	if (w3d->worldmap[w3d->mapx][w3d->mapy] > 2)
		w3d->color = 0xFF0000;
	else if (w3d->worldmap[w3d->mapx][w3d->mapy] == 2)
		w3d->color = 0xffffff;
	else if (w3d->raydiry > 0 && w3d->side == 1)
		w3d->color = 0x5cff43;
	else if (w3d->raydiry < 0 && w3d->side == 1)
		w3d->color = 0x6d82ff;
	else if (w3d->raydirx > 0 && w3d->side == 0)
		w3d->color = 0xffdb36;
	else if (w3d->raydirx < 0 && w3d->side == 0)
		w3d->color = 0xb91469;
}

void		ft_wolf(t_env *env, t_w3d *w3d)
{
	env->xi = 0;
	ft_init_wolf(env);
	while (env->xi < LENGHT)
	{
		ft_init_calc(env, w3d);
		ft_wolf_raydir(w3d);
		ft_wolf_walldistance(w3d);
		ft_wolf_calcdraw(env, w3d);
		ft_wolf_wallcolor(w3d);
		if (env->teleport == 0 && \
			w3d->worldmap[(int)w3d->posx][(int)w3d->posy] > 2)
		{
			env->teleport = 1;
			ft_teleport(w3d, w3d->worldmap[(int)w3d->posx][(int)w3d->posy]);
		}
		else if (env->teleport && \
				w3d->worldmap[(int)w3d->posx][(int)w3d->posy] < 2)
			env->teleport = 0;
		env->xf = env->xi;
		ft_draw_line(env, w3d->color);
		env->xi++;
	}
	if (env->minimap)
		ft_minimap(env, w3d);
}
