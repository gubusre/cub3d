#include "cub3d.h"

static int	rgb_value(char *str)
{
	int	i;
	int	value;

	i = 0;
	if (!str[0])
		return (-1);
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (-1);
	value = ft_atoi(str);
	if (value > 255)
		return (-1);
	return (value);
}

static int	rgb_to_int(char **rgb)
{
	int	color;
	int	value;
	int	i;

	i = 0;
	color = 0;
	while (i < 3)
	{
		if (!rgb[i])
			return (-1);
		value = rgb_value(rgb[i]);
		if (value < 0)
			return (-1);
		color = (color << 8) | value;
		i++;
	}
	if (rgb[3])
		return (-1);
	return (color);
}

int	parse_color(char *line, t_game *game, int id, int *found)
{
	char	**rgb;
	int		color;

	if (*found & (1 << id))
		return (error("duplicated element"), ERROR);
	*found |= (1 << id);
	while (*line == ' ')
		line++;
	rgb = ft_split(line, ',');
	if (!rgb)
		return (error("malloc failed"), ERROR);
	color = rgb_to_int(rgb);
	free_split(rgb);
	if (color < 0)
		return (error("invalid color"), ERROR);
	if (id == FLOOR)
		game->map.floor = color;
	else
		game->map.ceiling = color;
	return (OK);
}
