/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 11:51:07 by vroche            #+#    #+#             */
/*   Updated: 2015/05/19 12:07:48 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Main man !
** Init minilibx
** Init all struct
** Launch wolf3d
*/

#include "wolf3d.h"

static void	ft_usage(void)
{
	ft_putstr("Usage : ./wolf3d [map]\n\
.:| Key |:.\n\
...........\n\n\
w/s/a/d : Move\n\
Shift : Run\n\
m : Show minimap\n\
Esc : Exit!\n\
............\n\n");
}

static void	ft_init(t_env *env, t_w3d *w3d)
{
	if (!(env->img = mlx_new_image(env->mlx, LENGHT, HEIGHT)))
		ft_perror_exit("mlx_new_image() fails\n");
	env->data = mlx_get_data_addr(env->img, &(env->bpp), \
				&(env->sizeline), &(env->endian));
	if (!(env->imgsky = mlx_xpm_file_to_image(env->mlx, "./img/sky.xpm", \
						&(env->wsky), &(env->hsky))))
		ft_perror_exit("where is ./img/sky.xpm ?");
	env->sky = mlx_get_data_addr(env->imgsky, &(env->bpp2), \
				&(env->sizeline2), &(env->endian2));
	w3d->posx = 1.5;
	w3d->posy = 1.5;
	w3d->dirx = 0;
	w3d->diry = 1;
	w3d->planex = 0.66;
	w3d->planey = 0;
	w3d->movespeed = 0.05;
	w3d->rotspeed = 0.05;
	env->w3d = w3d;
	env->up = 0;
	env->down = 0;
	env->left = 0;
	env->right = 0;
	env->minimap = 0;
	env->teleport = 0;
}

int			main(int ac, char **av)
{
	t_env	env;
	t_w3d	w3d;

	if (ac >= 2)
		w3d.worldmap = ft_get_map(av[1]);
	else
		w3d.worldmap = ft_get_map("./map/map");
	if (!(env.mlx = mlx_init()))
		ft_perror_exit("mlx_init() fails\n");
	if (!(env.win = \
			mlx_new_window(env.mlx, LENGHT, HEIGHT, "wolf3d")))
		ft_perror_exit("mlx_new_window() fails to create a new window\n");
	ft_usage();
	ft_init(&env, &w3d);
	ft_wolf(&env, &w3d);
	mlx_hook(env.win, 2, 1, ft_key_press, &env);
	mlx_hook(env.win, 3, 2, ft_key_release, &env);
	mlx_expose_hook(env.win, ft_expose, &env);
	mlx_loop_hook(env.mlx, ft_key_event, &env);
	mlx_loop(env.mlx);
	return (0);
}
