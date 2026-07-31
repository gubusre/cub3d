#include "cub3d.h"


/*will have to think if will be need to check the line[1] == space or...*/
static int	is_config(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

int	parse_config(char **lines, t_game *game)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (lines[i])
	{
		if (lines[i][0] == '\0')
			i++;
		else if (is_config(lines[i]))
		{
			if (parse_element(lines[i], game, &found) != OK)
				return (-1);
			i++;
		}
		else
			break ;
	}
	if (found != 0x3F)
		return (error("missing or duplicated scene elements"), -1);
	return (i);
}

static char	*strip_newline(char *line)
{
	int	len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static int	count_lines(char *file)
{
	int fd;
	int	count;
	char *line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static char	**read_file(char * file)
{
	char	**lines;
	int		i;
	int		fd;
	int		count;

	count = count_lines(file);
	if (count <= 0)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = ft_calloc(count + 1, sizeof(char *));
	if (!lines)
		return (close(fd), NULL);
	i = 0;
	while (i < count)
		lines[i++] = strip_newline(get_next_line(fd));
	close(fd);
	return (lines);
}

int	parse_scene(char *file, t_game *game)
{
	char	**lines;
	int		i;

	lines = read_file(file);
	if (!lines)
		return (error("Can not read scene file"));
	i = parse_config(lines, game);
	if (i < 0)
		return (free_split(lines), ERROR);
	if (parse_map(lines + i, game) != OK) 
		return (free_split(lines), ERROR);
	free_split(lines);
	return (validate_map(game));
}