#include "cub3d.h"

static int	is_walkable(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map.width)
		return (0);
	if (map_y < 0 || map_y >= game->map.height)
		return (0);
	return (game->map.map[map_y][map_x] != '1');
}

static void	move(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + dx;
	new_y = game->player.pos_y + dy;
	if (is_walkable(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_walkable(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

static void	rotate(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}

int	handle_keypress(int key, t_game *game)
{
	if (key == KEY_ESC)
		return (close_window(game));
	if (key == KEY_W)
		move(game, game->player.dir_x * MOVE_SPEED,
			game->player.dir_y * MOVE_SPEED);
	if (key == KEY_S)
		move(game, -game->player.dir_x * MOVE_SPEED,
			-game->player.dir_y * MOVE_SPEED);
	if (key == KEY_A)
		move(game, game->player.dir_y * MOVE_SPEED,
			-game->player.dir_x * MOVE_SPEED);
	if (key == KEY_D)
		move(game, -game->player.dir_y * MOVE_SPEED,
			game->player.dir_x * MOVE_SPEED);
	if (key == KEY_LEFT)
		rotate(game, -ROT_SPEED);
	if (key == KEY_RIGHT)
		rotate(game, ROT_SPEED);
	return (0);
}
