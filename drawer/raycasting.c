/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:51:51 by maearly           #+#    #+#             */
/*   Updated: 2021/04/27 17:10:16 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void 	prep_calc(t_head *head, t_raycast *cast, int x)
{
	cast->camera_x = 2 * x / (double)head->screen.x - 1;
	cast->ray_dir_x = head->plr.dir_x + head->plr.plane_x * cast->camera_x;
	cast->ray_dir_y = head->plr.dir_y + head->plr.plane_y * cast->camera_x;
	cast->map_x = (int)head->plr.pos_x;
	cast->map_y = (int)head->plr.pos_y;
	cast->delta_dist_x = fabs(1 / cast->ray_dir_x);
	cast->delta_dist_y = fabs(1 / cast->ray_dir_y);
	cast->hit = 0;
}

void 	step_n_side_dist(t_head *head, t_raycast *cast)
{
	if (cast->ray_dir_x < 0)
	{
		cast->step_x = -1;
		cast->side_dist_x = (head->plr.pos_x - cast->map_x)
			* cast->delta_dist_x;
	}
	else
	{
		cast->step_x = 1;
		cast->side_dist_x = (cast->map_x + 1.0 - head->plr.pos_x)
			* cast->delta_dist_x;
	}
	if (cast->ray_dir_y < 0)
	{
		cast->step_y = -1;
		cast->side_dist_y = (head->plr.pos_y - cast->map_y)
			* cast->delta_dist_y;
	}
	else
	{
		cast->step_y = 1;
		cast->side_dist_y = (cast->map_y + 1.0 - head->plr.pos_y)
			* cast->delta_dist_y;
	}
}

void 	dda_algorithm(t_head *head, t_raycast *cast)
{
	while (cast->hit == 0)
	{
		if (cast->side_dist_x < cast->side_dist_y)
		{
			cast->side_dist_x += cast->delta_dist_x;
			cast->map_x += cast->step_x;
			cast->side = 0;
		}
		else
		{
			cast->side_dist_y += cast->delta_dist_y;
			cast->map_y += cast->step_y;
			cast->side = 1;
		}
		if (head->map[cast->map_y][cast->map_x] != '$')
		{
			if (head->map[cast->map_y][cast->map_x] == '1')
				cast->hit = 1;
			else if (head->map[cast->map_y][cast->map_x] == '2')
				sprite_on_fov(head, cast);
		}
	}
}

void	perp_dist(t_head *head, t_raycast *cast)
{
	if (cast->side == 0)
		cast->perp_wall_dist = (cast->map_x - head->plr.pos_x
				+ (1 - cast->step_x) / 2) / cast->ray_dir_x;
	else
		cast->perp_wall_dist = (cast->map_y - head->plr.pos_y
				+ (1 - cast->step_y) / 2) / cast->ray_dir_y;
}

void 	draw_start_end(t_head *head, t_raycast *cast)
{
	cast->draw_start = -cast->line_height / 2 + head->screen.y / 2;
	if (cast->draw_start < 0)
		cast->draw_start = 0;
	cast->draw_end = cast->line_height / 2 + head->screen.y / 2;
	if (cast->draw_end >= head->screen.y)
		cast->draw_end = head->screen.y - 1;
}
