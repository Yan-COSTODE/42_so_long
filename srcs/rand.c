/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:24:41 by ycostode          #+#    #+#             */
/*   Updated: 2023/12/04 16:58:21 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static unsigned int	update_seed(t_game *game)
{
	game->seed = game->seed * 1103515245 + 12345;
	return ((game->seed / 65536) % 32768);
}

int	random_number(t_game *game, int min, int max)
{
	int	range;
	int	rand;

	if (min > max)
		return (-1);
	range = max - min + 1;
	rand = update_seed(game) % range + min;
	return (rand);
}
