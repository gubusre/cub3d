#include "cub3d.h"

int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}
