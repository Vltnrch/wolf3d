/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 12:00:56 by vroche            #+#    #+#             */
/*   Updated: 2015/05/19 12:06:33 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define MAPWIDTH 30
# define MAPHEIGHT 30
# define LENGHT 1024
# define HEIGHT 768

typedef struct		s_w3d
{
	float			posx;
	float			posy;
	float			dirx;
	float			diry;
	float			planex;
	float			planey;
	float			camerax;
	float			rayposx;
	float			rayposy;
	float			raydirx;
	float			raydiry;
	int				mapx;
	int				mapy;
	float			sidedistx;
	float			sidedisty;
	float			deltadistx;
	float			deltadisty;
	float			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	size_t			color;
	float			movespeed;
	float			rotspeed;
	float			olddirx;
	float			oldplanex;
	int				**worldmap;
}					t_w3d;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*imgsky;
	int				bpp;
	int				bpp2;
	int				sizeline;
	int				endian;
	int				sizeline2;
	int				endian2;
	char			*data;
	char			*sky;
	int				wsky;
	int				hsky;
	float			xi;
	float			yi;
	float			xf;
	float			yf;
	int				up;
	int				down;
	int				left;
	int				right;
	int				shift;
	int				minimap;
	int				teleport;
	struct s_w3d	*w3d;
}					t_env;

typedef struct		s_draw
{
	int				dx;
	int				dy;
	int				i;
	int				xinc;
	int				yinc;
	int				cumul;
	int				x;
	int				y;
}					t_draw;

void				ft_draw_line(t_env *env, int color);

int					ft_key_release(int keycode, t_env *env);
int					ft_key_press(int keycode, t_env *env);
int					ft_key_event(t_env *env);

void				ft_put_pixel_to_image(size_t img_color, \
										t_env *env, int x, int y);
int					ft_expose(t_env *env);
void				ft_perror_exit(const char *str);

void				ft_minimap(t_env *env, t_w3d *w3d);

void				ft_init_calc(t_env *env, t_w3d *w3d);
void				ft_wolf_raydir(t_w3d *w3d);
void				ft_wolf_walldistance(t_w3d *w3d);
void				ft_wolf_calcdraw(t_env *env, t_w3d *w3d);

void				ft_teleport(t_w3d *w3d, int search);

void				ft_wolf(t_env *env, t_w3d *w3d);

int					**ft_get_map(const char *str);

char				**ft_nbrstrsplit(const char *s);

#endif
