#include "../includes/cub3d.h"

char	*advanced_get_next_line(int fd, int status)
{
	char	buff[1];
	char	line[1000000];
	int		i;
	int		n;

	i = 0;
	line[0] = 0;
	n = read(fd, buff, 1);
	while (n > 0)
	{
		line[i++] = buff[0];
		line[i] = '\0';
		if (buff[0] == '\n')
		{
			if (status == 0)
				line[i - 1] = '\0';
			return (ft_strdup(line));
		}
		n = read(fd, buff, 1);
	}
	if (!line[0])
		return (NULL);
	return (ft_strdup(line));
}
