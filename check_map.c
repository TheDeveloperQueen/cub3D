/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:38:52 by ritavasques       #+#    #+#             */
/*   Updated: 2024/09/25 10:18:05 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char    **read_map( char *map)
{
	int		fd;
	char	*temp_map;
	char	**map_read;
	int		bytesread;

	bytesread = 0;
	temp_map = (char *) ft_calloc(BUFF_SIZE + 1, sizeof(char));
	if (!temp_map)
		return (NULL);
	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		free(temp_map);
		return (NULL);
	}
	bytesread = read(fd, temp_map, BUFF_SIZE);
	if (bytesread <= 0)
	{
		free(temp_map);
		return (NULL);
	}
	map_read = ft_split(temp_map, '\n');
	free(temp_map);
	return (close(fd), map_read);
}

//File extencion of map must be .cub
int	check_cub(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	if (str[i] == 'b' && str[i - 1] == 'u' && str[i - 2] == 'c' &&
		str[i - 3] == '.')
		return(1);
	else
		return (0);
}

//Map must be surrounded by walls (spaces are valid)
static int	check_surrounded_walls(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->lines)
	{
		x = 0;
		while (x < data->columns)
		{
			if ((y == 0 || y == data->lines) && (data->map->map[y][x] != '1' && data->map->map[y][x] != ' '))
				return (0);
			if ((x == 0 || x == data->columns) && (data->map->map[y][x] != '1' && data->map->map[y][x] != ' '))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

//Only components 0, 1, N, S, E, W and space are valid
static int	check_components(t_data *data)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (y < data->lines)
	{
		while (x < data->columns)
		{
			if (data->map->map[y][x] != '0' && \
			data->map->map[y][x] != '1' && \
			data->map->map[y][x] != 'N' && \
			data->map->map[y][x] != 'S' && \
			data->map->map[y][x] != 'E' && \
			data->map->map[y][x] != 'W' && \
			data->map->map[y][x] != ' ')
			{
				return (1);
				break ;
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

//Check there's a player and only one
static int	check_player(t_data *data)
{
	int	y;
	int	x;
	int count;

	x = 0;
	y = 0;
	count = 0;
	while (y < data->lines)
	{
		while (x < data->columns)
		{
			if (data->map->map[y][x] == 'N' ||
			data->map->map[y][x] == 'S' ||
			data->map->map[y][x] == 'E' ||
			data->map->map[y][x] == 'W')
				count++;
			x++;
		}
		x = 0;
		y++;
	}
	if (count > 1 || count == 0)
		return (1);
	return (0);
}

//Check that map rules apply
int	map_ok(t_data *data)
{
	if (check_surrounded_walls(data) && !check_components(data) && !check_player(data))
		return (1);
	return (0);
}