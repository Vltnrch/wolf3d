/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 11:51:07 by vroche            #+#    #+#             */
/*   Updated: 2015/05/19 11:59:48 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_put_pixel_to_image (all is said)
** ft_expose : put image to window
** ft_perror_exit to manage error message and exit program
*/

#include "wolf3d.h"

void	ft_put_pixel_to_image(size_t img_color, t_env *env, int x, int y)
{
	char	*pixel;

	if (!(x >= 0 && x < LENGHT && y >= 0 && y < HEIGHT))
		return ;
	pixel = env->data + y * env->sizeline + x * env->bpp / 8;
	*pixel++ = (img_color & 0xFF);
	*pixel++ = (img_color & 0xFF00) >> 8;
	*pixel++ = (img_color & 0xFF0000) >> 16;
	*pixel = (img_color & 0xFF000000) >> 24;
}

int		ft_expose(t_env *env)
{
	if (!mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0))
		ft_perror_exit("mlx_new_window() fails to create a new window\n");
	return (0);
}

void	ft_perror_exit(const char *str)
{
	ft_putstr_fd("Error ", 2);
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}
