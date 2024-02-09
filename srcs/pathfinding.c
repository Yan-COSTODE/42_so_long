/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 23:47:36 by ycostode          #+#    #+#             */
/*   Updated: 2023/12/01 15:28:54 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static t_list	*ft_lstpop(t_list *list)
{
	t_list	*back;
	t_list	*current;

	back = ft_lstlast(list);
	current = list;
	while (current->next && current->next != back)
		current = current->next;
	current->next = NULL;
	return (back);
}

static void	neighbour(t_list **list, t_vector tmp, int i, t_params *params)
{
	t_vector	*next;
	t_vector	new;
	t_list		*lst;
	int			moves[8];

	init_moves(moves);
	new.x = tmp.x + moves[i];
	new.y = tmp.y + moves[4 + i];
	if (is_inside(params->map, new.x, new.y) && get_at(params->map, new.x,
			new.y) != '1' && get_at(params->map, new.x, new.y) != 'V'
		&& get_at(params->map, new.x, new.y) != params->obstacle)
	{
		next = malloc(sizeof(t_vector));
		next->x = new.x;
		next->y = new.y;
		lst = ft_lstnew(next);
		ft_lstadd_back(list, lst);
	}
}

static void	process(t_list **list, int *n, t_params *params)
{
	t_vector	tmp;
	t_list		*popped;
	int			i;

	popped = ft_lstpop(*list);
	tmp = *((t_vector *)popped->content);
	if (popped == *list)
		*list = NULL;
	ft_lstdelone(popped, free);
	if (get_at(params->map, tmp.x, tmp.y) == params->find)
		*n = *n + 1;
	change_at(&(params->map), tmp.x, tmp.y, 'V');
	i = 0;
	while (i < 4)
	{
		neighbour(list, tmp, i, params);
		++i;
	}
}

static int	count_reachable(int x, int y, t_params *params)
{
	int			n;
	t_list		*list;
	t_vector	*pos;

	n = 0;
	if (!is_inside(params->map, x, y) || get_at(params->map, x,
			y) != params->start)
		return (-1);
	pos = malloc(sizeof(t_vector));
	pos->x = x;
	pos->y = y;
	list = ft_lstnew(pos);
	while (ft_lstsize(list) > 0)
		process(&list, &n, params);
	ft_lstclear(&list, free);
	return (n);
}

void	parse_path(t_game *game)
{
	t_params	params;
	int			count;

	params.find = 'C';
	params.start = 'P';
	params.obstacle = 'E';
	params.map = mapdup(game->map);
	count = count_reachable(game->player.x, game->player.y, &params);
	free(params.map.map);
	if (count != game->map.egg)
		return (parse_error(&game->map,
				"All the collectibles aren't reachable"));
	params.find = 'E';
	params.start = 'P';
	params.obstacle = '1';
	params.map = mapdup(game->map);
	count = count_reachable(game->player.x, game->player.y, &params);
	free(params.map.map);
	if (count != 1)
		return (parse_error(&game->map, "The exit isn't reachable"));
}
