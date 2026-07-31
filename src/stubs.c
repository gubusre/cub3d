#include "cub3d.h"

/* TODO: implementar */
int	parse_texture(char *line, t_game *game, int id, int *found)
{
	(void)line;
	(void)game;
	if (*found & (1 << id))
		return (error("duplicated element"), ERROR);
	*found |= (1 << id);
	return (OK);
}

/* TODO: implementar */
int	parse_color(char *line, t_game *game, int id, int *found)
{
	(void)line;
	(void)game;
	if (*found & (1 << id))
		return (error("duplicated element"), ERROR);
	*found |= (1 << id);
	return (OK);
}

/* TODO: implementar */
int	parse_map(char **lines, t_game *game)
{
	(void)lines;
	(void)game;
	return (OK);
}

/* TODO: implementar */
int	validate_map(t_game *game)
{
	(void)game;
	return (OK);
}

/* TODO: implementar (B) */
int	render_frame(t_game *game)
{
	(void)game;
	return (0);
}

/* TODO: implementar (B) */
int	handle_keypress(int key, t_game *game)
{
	(void)key;
	(void)game;
	return (0);
}

/* TODO: implementar (B) */
int	close_window(t_game *game)
{
	(void)game;
	exit(0);
	return (0);
}

/* TODO: implementar */
void	free_game(t_game *game)
{
	(void)game;
}

/* TODO: implementar */
int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error("mlx_init failed"));
	return (OK);
}

/* TODO: implementar */
int	init_frame(t_game *game)
{
	(void)game;
	return (OK);
}