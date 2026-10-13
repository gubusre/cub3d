#include "cub3d.h"

static void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				put_pixel(&game->frame, x, y, game->map.ceiling);
			else
				put_pixel(&game->frame, x, y, game->map.floor);
			x++;
		}
		y++;
	}
}

int	render_frame(t_game *game)
{
	int	x;

	draw_background(game);
	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_ray(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
	return (OK);
}
