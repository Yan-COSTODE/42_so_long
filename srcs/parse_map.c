/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:58:29 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/02 15:40:57 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <fcntl.h>
#include <unistd.h>

static t_string	parse_char(t_map *map, int fd)
{
	char	*file;
	char	*tmp;
	int		bytes;
	char	buf[READ_SIZE];

	bytes = 1;
	file = (char *)ft_calloc(1, sizeof(char));
	while (bytes != 0)
	{
		bytes = read(fd, buf, READ_SIZE - 1);
		if (bytes == -1)
		{
			parse_error(map, "Can't read the file");
			free(file);
			return (NULL);
		}
		if (bytes < READ_SIZE)
			buf[bytes] = 0;
		tmp = file;
		file = ft_strjoin(file, buf);
		free(tmp);
	}
	return (file);
}

static void	parse_map_wall(t_map *map)
{
	t_string	str;
	int			i;

	i = 0;
	str = map->map;
	while (str[i])
	{
		if (map->height == 0)
			map->width = i + 1;
		if (str[i] == '\n' || str[i + 1] == '\0')
			map->height++;
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '\n')
			return (parse_error(map, "The map need to be closed by walls"));
		if (i != 0 && i % map->width == 0 && (i / map->width) != map->height
			- 1)
			i += map->width - 2;
		else
			i++;
	}
}

static void	parse_map_comp(t_map *map)
{
	int			comp[3];
	int			i;

	init_comp(&i, comp);
	while (map->map[++i])
	{
		if (map->map[i] == 'C')
			++comp[0];
		else if (map->map[i] == 'E')
			++comp[1];
		else if (map->map[i] == 'P')
			++comp[2];
		else if (map->map[i] != '0' && map->map[i] != '1'
			&& map->map[i] != '\n')
			return (parse_error(map, "The map contains unknowm character"));
		if (i != 0 && map->map[i] == '\n' && map->map[i - 1] == '\n')
			return (parse_error(map, "The map contains empty line"));
	}
	map->egg = comp[0];
	if (comp[0] < 1)
		return (parse_error(map, "The map doesn't have collectible"));
	if (comp[1] != 1)
		return (parse_error(map, "The map doesn't have 1 exit"));
	if (comp[2] != 1)
		return (parse_error(map, "The map doesn't have 1 starting position"));
}

static void	parse_file(t_map *map, int fd)
{
	map->map = parse_char(map, fd);
	if (!map->map)
		return (parse_error(map, "Can't properly read the file"));
	map->height = 0;
	map->width = 0;
	parse_map_comp(map);
	if (map->parsed == true)
		parse_map_wall(map);
}

void	parse_map(t_map *map, const t_string file)
{
	int	fd;
	int	len;

	map->map = NULL;
	len = ft_strlen(file);
	if (len >= 4 && ft_strncmp(&file[len - 4], ".ber", 4) != 0)
		return (parse_error(map, "Wrong file types"));
	else if (len < 4)
		return (parse_error(map, "Wrong file types"));
	map->parsed = true;
	if (!file)
		return (parse_error(map, "No file given"));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (parse_error(map, "Can't open the file"));
	parse_file(map, fd);
	close(fd);
}
