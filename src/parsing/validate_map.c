#include "cub3d.h"

static void	set_player(t_game *game, char c, int x, int y)
{
	game->player.pos_x = x + 0.5;
	game->player.pos_y = y + 0.5;
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	if (c == 'N')
		game->player.dir_y = -1;
	else if (c == 'S')
		game->player.dir_y = 1;
	else if (c == 'E')
		game->player.dir_x = 1;
	else
		game->player.dir_x = -1;
	game->player.plane_x = -game->player.dir_y * 0.66;
	game->player.plane_y = game->player.dir_x * 0.66;
}

static int	check_chars(t_game *game, int *count)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.map[y][x];
			if (!ft_strchr("01NSEW ", c))
				return (error("invalid character in map"), ERROR);
			if (ft_strchr("NSEW", c))
			{
				(*count)++;
				set_player(game, c, x, y);
			}
			x++;
		}
		y++;
	}
	return (OK);
}

static int	has_gap(t_game *game, int x, int y)
{
	if (y == 0 || y == game->map.height - 1)
		return (1);
	if (x == 0 || x == game->map.width - 1)
		return (1);
	if (game->map.map[y - 1][x] == ' ' || game->map.map[y + 1][x] == ' ')
		return (1);
	if (game->map.map[y][x - 1] == ' ' || game->map.map[y][x + 1] == ' ')
		return (1);
	return (0);
}

static int	check_closed(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (ft_strchr("0NSEW", game->map.map[y][x])
				&& has_gap(game, x, y))
				return (error("map is not closed"), ERROR);
			x++;
		}
		y++;
	}
	return (OK);
}

int	validate_map(t_game *game)
{
	int	count;

	count = 0;
	if (check_chars(game, &count) != OK)
		return (ERROR);
	if (count != 1)
		return (error("map needs exactly one player"), ERROR);
	return (check_closed(game));
}
