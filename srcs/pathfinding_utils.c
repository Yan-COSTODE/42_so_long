/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:39:33 by ycostode          #+#    #+#             */
/*   Updated: 2023/11/30 18:02:19 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_map	mapdup(t_map map)
{
	t_map	new;

	new.egg = map.egg;
	new.height = map.height;
	new.width = map.width;
	new.parsed = map.parsed;
	new.map = ft_strdup(map.map);
	return (new);
}

void	init_moves(int moves[8])
{
	moves[0] = -1;
	moves[1] = 1;
	moves[2] = 0;
	moves[3] = 0;
	moves[4 + 0] = 0;
	moves[4 + 1] = 0;
	moves[4 + 2] = -1;
	moves[4 + 3] = 1;
}

int	is_inside(t_map map, int x, int y)
{
	return (x >= 0 && x < map.width - 1 && y >= 0 && y < map.height);
}
