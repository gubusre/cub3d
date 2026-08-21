#include "cub3d.h"

int	parse_texture(char *line, t_game *game, int id, int *found)
{
	if (*found & (1 << id))
		return (error("duplicated element"), ERROR);
	*found |= (1 << id);
	while(*line == ' ')
		line++;
	game->texture[id].ptr = mlx_xpm_file_to_image(game->mlx, line,
		&game->texture[id].width, &game->texture[id].height);
	if(!game->texture[id].ptr)
		return (error("can not load texure"), ERROR);
	game->texture[id].data = mlx_get_data_addr(game->texture[id].ptr,
							&game->texture[id].bpp, &game->texture[id].line_len,
							&game->texture[id].endian);
	return (OK);
}