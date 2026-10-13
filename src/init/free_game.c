#include "cub3d.h"

static void	free_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture[i].ptr)
			mlx_destroy_image(game->mlx, game->texture[i].ptr);
		i++;
	}
	if (game->frame.ptr)
		mlx_destroy_image(game->mlx, game->frame.ptr);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx)
		free_images(game);
	if (game->map.map)
		free_split(game->map.map);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
