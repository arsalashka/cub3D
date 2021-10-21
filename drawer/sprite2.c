/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 20:27:24 by maearly           #+#    #+#             */
/*   Updated: 2021/04/29 14:32:36 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	spr_draw_calc(t_head *head, t_sprite_draw *draw, int i)
{
	draw->sprite_x = head->sorted[i].pos.x - head->plr.pos_x;
	draw->sprite_y = head->sorted[i].pos.y - head->plr.pos_y;
	draw->inv_det = 1.0 / (head->plr.plane_x * head->plr.dir_y
			- head->plr.dir_x * head->plr.plane_y);
	draw->transform_x = draw->inv_det * (head->plr.dir_y * draw->sprite_x
			- head->plr.dir_x * draw->sprite_y);
	draw->transform_y = draw->inv_det * (-head->plr.plane_y * draw->sprite_x
			+ head->plr.plane_x * draw->sprite_y);
	draw->spr_screen_x = (int)((head->screen.x / 2) * (1 + draw->transform_x
				/ draw->transform_y));
	draw->spr_height = abs((int)(head->screen.y / draw->transform_y));
}

void	spr_draw_calc2(t_head *head, t_sprite_draw *draw)
{
	draw->spr_height = abs((int)(head->screen.y / draw->transform_y));
	draw->draw_start_y = -(draw->spr_height) / 2 + head->screen.y / 2;
	if (draw->draw_start_y < 0)
		draw->draw_start_y = 0;
	draw->draw_end_y = draw->spr_height / 2 + head->screen.y / 2;
	if (draw->draw_end_y >= head->screen.y)
		draw->draw_end_y = head->screen.y - 1;
	draw->spr_width = abs((int)(head->screen.y / (draw->transform_y)));
	draw->draw_start_x = -draw->spr_width / 2 + draw->spr_screen_x;
	if (draw->draw_start_x < 0)
		draw->draw_start_x = 0;
	draw->draw_end_x = draw->spr_width / 2 + draw->spr_screen_x;
	if (draw->draw_end_x >= head->screen.x)
		draw->draw_end_x = head->screen.x - 1;
}

void	spr_drawer(t_head *head, t_sprite_draw *draw, double const *z_buff)
{
	draw->stripe = draw->draw_start_x - 1;
	while (++draw->stripe < draw->draw_end_x)
	{
		draw->tex_x = (int)(256 * (draw->stripe - (-draw->spr_width / 2
						+ draw->spr_screen_x)) * head->tex[4]->width
				/ draw->spr_width) / 256;
		if (draw->transform_y > 0 && draw->stripe > 0
			&&draw->stripe < head->screen.x
			&& draw->transform_y < z_buff[draw->stripe])
		{
			draw->y = draw->draw_start_y - 1;
			while (++draw->y < draw->draw_end_y)
			{
				draw->d = (draw->y) * 256 - head->screen.y * 128
					+ draw->spr_height * 128;
				draw->tex_y = ((draw->d * head->tex[4]->height)
						/ draw->spr_height) / 256;
				draw->color = get_tex_color(head->tex[4], draw->tex_x, draw
						->tex_y);
				if ((draw->color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(&head->win, draw->stripe, draw->y,
						draw->color);
			}
		}
	}
}
