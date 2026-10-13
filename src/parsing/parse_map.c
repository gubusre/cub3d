#include "cub3d.h"

static int	measure_map(char **lines, int *width)
{
	int	height;

	height = 0;
	*width = 0;
	while (lines[height])
	{
		if ((int)ft_strlen(lines[height]) > *width)
			*width = ft_strlen(lines[height]);
		height++;
	}
	return (height);
}

static char	*copy_row(char *src, int width)
{
	char	*row;
	int		len;
	int		i;

	row = ft_calloc(width + 1, sizeof(char));
	if (!row)
		return (NULL);
	len = ft_strlen(src);
	i = 0;
	while (i < width)
	{
		if (i < len)
			row[i] = src[i];
		else
			row[i] = ' ';
		i++;
	}
	return (row);
}

int	parse_map(char **lines, t_game *game)
{
	int	i;

	game->map.height = measure_map(lines, &game->map.width);
	if (game->map.height == 0)
		return (error("empty map"), ERROR);
	game->map.map = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.map)
		return (error("malloc failed"), ERROR);
	i = 0;
	while (i < game->map.height)
	{
		game->map.map[i] = copy_row(lines[i], game->map.width);
		if (!game->map.map[i])
			return (error("malloc failed"), ERROR);
		i++;
	}
	return (OK);
}
