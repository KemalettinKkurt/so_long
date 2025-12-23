/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: generated <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by generated         #+#    #+#             */
/*   Updated: 2025/12/23 00:00:00 by generated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <X11/keysym.h>

static void	move_player(t_game *game, int dx, int dy)
{
	int		nx;
	int		ny;
	char	dest;

	nx = game->map.player_x + dx;
	ny = game->map.player_y + dy;
	if (nx < 0 || ny < 0 || nx >= game->map.width || ny >= game->map.height)
		return ;
	dest = game->map.grid[ny][nx];
	if (dest == '1')
		return ;
	if (dest == 'E' && game->map.collectibles > 0)
		return ;
	if (dest == 'C')
	{
		game->map.collectibles--;
		game->map.grid[ny][nx] = '0';
	}
	game->map.player_x = nx;
	game->map.player_y = ny;
	game->moves++;
	print_move_count(game->moves);
	render_map(game);
	if (dest == 'E')
	{
		ft_putstr_fd("Congratulations! You won!\n", 1);
		close_game(game);
	}
}

int	handle_key(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		close_game(game);
	else if (keysym == XK_w || keysym == XK_W || keysym == XK_Up)
		move_player(game, 0, -1);
	else if (keysym == XK_s || keysym == XK_S || keysym == XK_Down)
		move_player(game, 0, 1);
	else if (keysym == XK_a || keysym == XK_A || keysym == XK_Left)
		move_player(game, -1, 0);
	else if (keysym == XK_d || keysym == XK_D || keysym == XK_Right)
		move_player(game, 1, 0);
	return (0);
}

