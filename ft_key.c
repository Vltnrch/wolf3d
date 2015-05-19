/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 11:59:13 by vroche            #+#    #+#             */
/*   Updated: 2015/05/19 12:01:52 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** All key managements fonctions
** ft_key_event for camera rotation and camera translation (with hit wall check)
** ft_key_release check a release of key
** ft_key_press check pression of key
*/

#include "wolf3d.h"

static void	ft_key_event_updown(t_env *env, t_w3d *w3d)
{
	if (env->up == 1)
	{
		if (w3d->worldmap[(int)(w3d->posx + w3d->dirx * w3d->movespeed)]\
						[(int)w3d->posy] != 1)
			w3d->posx += w3d->dirx * w3d->movespeed;
		if (w3d->worldmap[(int)w3d->posx]\
						[(int)(w3d->posy + w3d->diry * w3d->movespeed)] != 1)
			w3d->posy += w3d->diry * w3d->movespeed;
	}
	else if (env->down == 1)
	{
		if (w3d->worldmap[(int)(w3d->posx - w3d->dirx * w3d->movespeed)]\
						[(int)w3d->posy] != 1)
			w3d->posx -= w3d->dirx * w3d->movespeed;
		if (w3d->worldmap[(int)w3d->posx]\
						[(int)(w3d->posy - w3d->diry * w3d->movespeed)] != 1)
			w3d->posy -= w3d->diry * w3d->movespeed;
	}
}

static void	ft_key_event_leftright(t_env *env, t_w3d *w3d)
{
	w3d->olddirx = w3d->dirx;
	w3d->oldplanex = w3d->planex;
	if (env->right == 1)
	{
		w3d->dirx = w3d->dirx * cos(-w3d->rotspeed) \
					- w3d->diry * sin(-w3d->rotspeed);
		w3d->diry = w3d->olddirx * sin(-w3d->rotspeed) \
					+ w3d->diry * cos(-w3d->rotspeed);
		w3d->planex = w3d->planex * cos(-w3d->rotspeed) \
					- w3d->planey * sin(-w3d->rotspeed);
		w3d->planey = w3d->oldplanex * sin(-w3d->rotspeed) \
					+ w3d->planey * cos(-w3d->rotspeed);
	}
	else if (env->left == 1)
	{
		w3d->dirx = w3d->dirx * cos(w3d->rotspeed) \
					- w3d->diry * sin(w3d->rotspeed);
		w3d->diry = w3d->olddirx * sin(w3d->rotspeed) \
					+ w3d->diry * cos(w3d->rotspeed);
		w3d->planex = w3d->planex * cos(w3d->rotspeed) \
					- w3d->planey * sin(w3d->rotspeed);
		w3d->planey = w3d->oldplanex * sin(w3d->rotspeed) \
					+ w3d->planey * cos(w3d->rotspeed);
	}
}

int			ft_key_event(t_env *env)
{
	t_w3d	*w3d;

	w3d = env->w3d;
	ft_key_event_updown(env, w3d);
	ft_key_event_leftright(env, w3d);
	if (env->shift == 1)
	{
		w3d->movespeed = 0.08;
		w3d->rotspeed = 0.08;
	}
	else
	{
		w3d->movespeed = 0.04;
		w3d->rotspeed = 0.04;
	}
	ft_wolf(env, env->w3d);
	ft_expose(env);
	return (0);
}

int			ft_key_release(int keycode, t_env *env)
{
	if (keycode == 13)
		env->up = 0;
	else if (keycode == 1)
		env->down = 0;
	else if (keycode == 2)
		env->right = 0;
	else if (keycode == 0)
		env->left = 0;
	else if (keycode == 257)
		env->shift = 0;
	return (0);
}

int			ft_key_press(int keycode, t_env *env)
{
	t_w3d *w3d;

	w3d = env->w3d;
	if (keycode == 53)
		exit(0);
	else if (keycode == 46)
		env->minimap = env->minimap == 0 ? 1 : 0;
	else if (keycode == 13)
		env->up = 1;
	else if (keycode == 1)
		env->down = 1;
	else if (keycode == 2)
		env->right = 1;
	else if (keycode == 0)
		env->left = 1;
	else if (keycode == 257)
		env->shift = 1;
	return (0);
}
