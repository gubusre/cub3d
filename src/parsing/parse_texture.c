#include "cub3d.h"

int	parse_texture(char *line, t_game *game, int id, int *found)
{
	t_img	*tex;

	if (*found & (1 << id))
		return (error("duplicated element"), ERROR);
	*found |= (1 << id);
	while (*line == ' ')
		line++;
	tex = &game->texture[id];
	tex->ptr = mlx_xpm_file_to_image(game->mlx, line,
			&tex->width, &tex->height);
	if (!tex->ptr)
		return (error("cannot load texture"), ERROR);
	tex->data = mlx_get_data_addr(tex->ptr, &tex->bpp,
			&tex->line_len, &tex->endian);
	return (OK);
}
