#include "cub3d.h"

static char	*copy_row(char *src, int width)
{
	char	*row;
	int		i;

	row = ft_calloc(width + 1, sizeof(char));
	if (!row)
		return (NULL);
	i = 0;
	while (i < width)
	{
		if (src[i])
			row[i] = src[i];
		else
			row[i] = ' ';
		i++;
	}
	return (row);
}

int	parse_map(char **lines, t_game *game)
{
	int	height;
	int	width;
	int	i;

	height = 0;
	width = 0;
	while (lines[height])
	{
		if ((int)ft_strlen(lines[height]) > width)
			width = ft_strlen(lines[height]);
		height++;
	}
	if (height == 0)
		return (error("empty map"), ERROR);
	game->map.map = ft_calloc(height + 1, sizeof(char *));
	if (!game->map.map)
		return (error("malloc failed"), ERROR);
	i = 0;
	while (i < height)
	{
		game->map.map[i] = copy_row(lines[i], width);
		if (!game->map.map[i])
			return (free_split(game->map.map), error("malloc failed"), ERROR);
		i++;
	}
	game->map.height = height;
	game->map.width = width;
	return (OK);
}