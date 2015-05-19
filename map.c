/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 11:51:07 by vroche            #+#    #+#             */
/*   Updated: 2015/05/19 12:08:02 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_get_map get map in argument file and return map in int**
** apply security wall in border
** put 0 in all blank
** check if all number are between 0 and 2
** 0 floor
** 1 wall
** 2 pass throught the wall
*/

#include "wolf3d.h"

static void	ft_security_wall(int **map)
{
	int			i;

	i = 0;
	while (i < MAPWIDTH)
		map[0][i++] = 1;
	i = 0;
	while (i < MAPWIDTH)
		map[MAPHEIGHT - 1][i++] = 1;
	i = 0;
	while (i < MAPHEIGHT)
		map[i++][0] = 1;
	i = 0;
	while (i < MAPHEIGHT)
		map[i++][MAPWIDTH - 1] = 1;
}

static void	ft_init_map(int **map)
{
	int			i;
	int			j;

	i = 0;
	while (i < MAPWIDTH)
	{
		j = 0;
		while (j < MAPHEIGHT)
			map[i][j++] = 0;
		i++;
	}
	return ;
}

static void	ft_free_ptrs(char **map_char)
{
	int			i;

	i = 0;
	while (map_char[i])
		free(map_char[i++]);
	free(map_char);
	return ;
}

static void	ft_fill_map(int **map, int fd)
{
	int			i;
	int			j;
	char		*line;
	char		**map_char;
	char		**tmp;

	i = 0;
	while (i < MAPWIDTH && get_next_line(fd, &line) > 0)
	{
		j = 0;
		map_char = ft_nbrstrsplit(line);
		free(line);
		tmp = map_char;
		while (j < MAPHEIGHT && *map_char)
		{
			map[i][j] = ft_atoi(*map_char++);
			if (map[i][j] < 0 || map[i][j] > 9)
				ft_perror_exit("Invalid map. Reason: invalid values.");
			j++;
		}
		ft_free_ptrs(tmp);
		i++;
	}
}

int			**ft_get_map(const char *str)
{
	int			**map;
	int			i;
	int			fd;

	map = NULL;
	if (!(map = (int **)malloc(sizeof(int *) * (MAPWIDTH + 1))))
		ft_perror_exit("malloc()");
	i = 0;
	while (i < MAPWIDTH)
	{
		if (!(map[i] = (int *)malloc(sizeof(int) * (MAPHEIGHT + 1))))
			ft_perror_exit("malloc()");
		i++;
	}
	ft_init_map(map);
	if ((fd = open(str, O_RDONLY)) == -1)
		ft_perror_exit("open()");
	ft_fill_map(map, fd);
	ft_security_wall(map);
	close(fd);
	return (map);
}
