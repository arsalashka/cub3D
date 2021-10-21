/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:07:11 by maearly           #+#    #+#             */
/*   Updated: 2021/04/29 14:27:43 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void 	spr_dist_calc(t_head *head, t_sprite *to_sort, int count)
{
	double	dist;
	int		i;

	i = -1;
	while (++i < count)
	{
		dist = ((head->plr.pos_x - to_sort[i].pos.x)
				* (head->plr.pos_x - to_sort[i].pos.x))
			+ ((head->plr.pos_y - to_sort[i].pos.y)
				* (head->plr.pos_y - to_sort[i].pos.y));
		to_sort[i].dist = dist;
	}
}

t_sprite	*sort_sprites(t_head *head, t_sprite *to_sort, int count)
{
	t_sprite	tmp;
	int			i;
	int			k;

	spr_dist_calc(head, to_sort, count);
	i = 0;
	while (++i < count)
	{
		k = i;
		while (k > 0 && to_sort[k - 1].dist > to_sort[k].dist)
		{
			tmp = to_sort[k];
			to_sort[k] = to_sort[k - 1];
			to_sort[k - 1] = tmp;
			k--;
		}
	}
	return (to_sort);
}

t_sprite	*sprite_malloc(t_head *head, t_sprite *to_sort, int *count)
{
	int	j;
	int	k;

	j = -1;
	*count = 0;
	while (++j < head->spr_count)
		if (head->sprites[j].flag == 1)
			*count = *count + 1;
	to_sort = malloc(sizeof(t_sprite) * (*count));
	if (!to_sort)
		ft_error(head, "Error\nMalloc error!\n");
	j = -1;
	k = -1;
	while (++j < head->spr_count)
	{
		if (head->sprites[j].flag == 1)
			to_sort[++k] = head->sprites[j];
	}
	return (to_sort);
}

void	sprite_calc(t_head *head, double const *z_buff)
{
	t_sprite_draw	draw;
	t_sprite		*to_sort;
	int				i;
	int				count;

	to_sort = NULL;
	to_sort = sprite_malloc(head, to_sort, &count);
	head->sorted = sort_sprites(head, to_sort, count);
	i = count;
	while (--i >= 0)
	{
		spr_draw_calc(head, &draw, i);
		spr_draw_calc2(head, &draw);
		spr_drawer(head, &draw, z_buff);
	}
	free(head->sorted);
}
