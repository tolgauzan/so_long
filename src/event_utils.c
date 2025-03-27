/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuzan <tuzan@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:29:58 by tuzan             #+#    #+#             */
/*   Updated: 2025/03/28 00:29:58 by tuzan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_dynamic_color(t_color *color)
{
	color->r = (color->r + 3) % 256;
	color->g = (color->g + 5) % 256;
	color->b = (color->b + 7) % 256;
	if (color->r < 180)
		color->r = 180;
	if (color->g < 180)
		color->g = 180;
	if (color->b < 180)
		color->b = 180;
	return ((color->a << 24) | (color->r << 16) | (color->g << 8) | color->b);
}
