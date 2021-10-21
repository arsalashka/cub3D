/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:08:52 by maearly           #+#    #+#             */
/*   Updated: 2021/04/27 17:24:09 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void 	wall_x_calc(t_head *head, t_raycast *cast)
{
	if (cast->side == 0)
	{
		cast->wall_x = head->plr.pos_y + cast->perp_wall_dist * cast->ray_dir_y;
		cast->tex_num = 2;
	}
	else
	{
		cast->wall_x = head->plr.pos_x + cast->perp_wall_dist * cast->ray_dir_x;
		cast->tex_num = 1;
	}
	cast->wall_x -= floor((cast->wall_x));
}

void 	tex_x(t_head *head, t_raycast *cast)
{
	cast->tex_x = (int)(cast->wall_x
			* (double)(head->tex[cast->tex_num]->width));
	if (cast->side == 0 && cast->ray_dir_x > 0)
	{
		cast->tex_num = 3;
		cast->tex_x = head->tex[cast->tex_num]->width - cast->tex_x - 1;
	}
	if (cast->side == 1 && cast->ray_dir_y < 0)
	{
		cast->tex_num = 0;
		cast->tex_x = head->tex[cast->tex_num]->width - cast->tex_x - 1;
	}
}

void 	draw_ceiling_floor(t_head *head, t_raycast *cast, int x)
{
	int	y;

	y = -1;
	while (++y < cast->draw_start)
		my_mlx_pixel_put(&head->win, x, y, head->skyline.c_color);
	y = cast->draw_end;
	while (++y < head->screen.y)
		my_mlx_pixel_put(&head->win, x, y, head->skyline.f_color);
}

void 	draw_line(t_head *head, t_raycast *cast, int x, double *z_buff)
{
	cast->step = 1.0 * head->tex[cast->tex_num]->height / cast->line_height;
	cast->tex_pos = (cast->draw_start - head->screen.y / 2 + cast->line_height
			/ 2) * cast->step;
	cast->y = cast->draw_start;
	while (cast->y <= cast->draw_end)
	{
		cast->tex_y = (int)cast->tex_pos
			& (head->tex[cast->tex_num]->height - 1);
		cast->tex_pos += cast->step;
		cast->color = get_tex_color(head->tex[cast->tex_num], cast->tex_x,
				cast->tex_y);
		my_mlx_pixel_put(&head->win, x, cast->y, cast->color);
		cast->y++;
		z_buff[x] = cast->perp_wall_dist;
	}
}

void	sprite_on_fov(t_head *head, t_raycast *cast)
{
	int	i;

	i = -1;
	while (++i < head->spr_count)
	{
		if (head->sprites[i].flag != 1
			&& head->sprites[i].pos.y == cast->map_y
			&& head->sprites[i].pos.x == cast->map_x)
			head->sprites[i].flag = 1;
	}
}
