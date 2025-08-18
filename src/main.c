/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tignatov <tignatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:58:39 by tignatov          #+#    #+#             */
/*   Updated: 2025/08/18 14:40:52 by tignatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main (int argc, char **argv)
{
    t_game  game;
    
    if (is_valid_input(argc, argv) == false)
        return (1);
    parse_map(&game, argv[1]);
}  