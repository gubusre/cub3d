#include "cub3d.h"

int	main (int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
		return (error("Usage: ./cub3d <map.cub>"));
	ft_bzero(&game, sizeof(t_game));
	if (init_mlx(&game) != OK)
		return (ERROR);	
	if (parse_scene(argv[1], &game) != OK)
		return (free_game(&game), ERROR);

	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if(!game.win)
		return (free_game(&game), error("window failed"));
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_loop(game.mlx);
	return (0);
}