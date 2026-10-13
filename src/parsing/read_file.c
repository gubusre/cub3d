#include "cub3d.h"

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
	int		fd;
	int		count;
	char	*line;

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

char	**read_file(char *file)
{
	char	**lines;
	int		fd;
	int		count;
	int		i;

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
