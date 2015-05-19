/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 13:09:02 by vroche            #+#    #+#             */
/*   Updated: 2015/05/03 20:35:36 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_nbrstrsplit is like split() / cut all number in char **
*/

#include "wolf3d.h"

static int	ft_cnt_parts(const char *s)
{
	int		cnt;
	int		in_substring;

	in_substring = 0;
	cnt = 0;
	while (*s != '\0')
	{
		if (in_substring == 1 && !((*s >= '0' && *s <= '9') || \
			*s == '-' || *s == '+'))
			in_substring = 0;
		if (in_substring == 0 && ((*s >= '0' && *s <= '9') \
			|| *s == '-' || *s == '+'))
		{
			in_substring = 1;
			cnt++;
		}
		s++;
	}
	return (cnt);
}

static int	ft_wlen(const char *s)
{
	int		len;

	len = 0;
	while (((*s >= '0' && *s <= '9') || *s == '-' || *s == '+') && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char		**ft_nbrstrsplit(const char *s)
{
	char	**t;
	int		nb_word;
	int		index;

	index = 0;
	nb_word = ft_cnt_parts((const char *)s);
	t = NULL;
	t = (char **)malloc(sizeof(*t) * (ft_cnt_parts((const char *)s) + 1));
	if (t == NULL)
		ft_perror_exit("malloc():");
	while (nb_word--)
	{
		while (!((*s >= '0' && *s <= '9') || *s == '-' || *s == '+') \
			&& *s != '\0')
			s++;
		t[index] = NULL;
		t[index] = ft_strsub((const char *)s, 0, ft_wlen((const char *)s));
		if (t[index] == NULL)
			ft_perror_exit("malloc():");
		s = s + ft_wlen(s);
		index++;
	}
	t[index] = NULL;
	return (t);
}
