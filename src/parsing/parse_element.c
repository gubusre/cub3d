#include "cub3d.h"

int		parse_element(char *line, t_game *game, int *found)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture(line + 2, game, NO, found));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture(line + 2, game, SO, found));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture(line + 2, game, WE, found));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture(line + 2, game, EA, found));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(line + 1, game, FLOOR, found));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(line + 1, game, CEILING, found));
	return (error("unknown identifier"), ERROR);
}
