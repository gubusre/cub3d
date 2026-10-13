#include "cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error("mlx_init failed"));
	return (OK);
}

int	init_frame(t_game *game)
{
	game->frame.ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->frame.ptr)
		return (error("mlx_new_image failed"));
	game->frame.data = mlx_get_data_addr(game->frame.ptr, &game->frame.bpp,
			&game->frame.line_len, &game->frame.endian);
	game->frame.width = WIN_WIDTH;
	game->frame.height = WIN_HEIGHT;
	return (OK);
}
