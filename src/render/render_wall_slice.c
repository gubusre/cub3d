#include "cub3d.h"

static int	get_texture_id(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (EA);
		return (WE);
	}
	if (ray->step_y > 0)
		return (SO);
	return (NO);
}

void	render_wall_slice(t_game *game, t_ray *ray, int x)
{
	t_img	*tex;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;

	if (ray->line_height <= 0)
		return ;
	tex = &game->texture[get_texture_id(ray)];
	tex_x = (int)(ray->wall_x * tex->width);
	if ((ray->side == 0 && ray->step_x < 0)
		|| (ray->side == 1 && ray->step_y > 0))
		tex_x = tex->width - tex_x - 1;
	step = (double)tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		put_pixel(&game->frame, x, y,
			get_texture_pixel(tex, tex_x, (int)tex_pos));
		tex_pos += step;
		y++;
	}
}
