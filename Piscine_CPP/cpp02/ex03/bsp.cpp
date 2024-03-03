/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reshivii <reshivii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:40:05 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/02 20:51:04 by reshivii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"
#include <iostream>

bool bsp(Point const a, Point const b, Point const c, Point const point) {
    Fixed const a1 = Fixed(b.getY() - a.getY()) * Fixed(point.getX() - a.getX()) - Fixed(b.getX() - a.getX()) * Fixed(point.getY() - a.getY());
    Fixed const a2 = Fixed(c.getY() - b.getY()) * Fixed(point.getX() - b.getX()) - Fixed(c.getX() - b.getX()) * Fixed(point.getY() - b.getY());
    Fixed const a3 = Fixed(a.getY() - c.getY()) * Fixed(point.getX() - c.getX()) - Fixed(a.getX() - c.getX()) * Fixed(point.getY() - c.getY());

    return (a1 >= Fixed(0) && a2 >= Fixed(0) && a3 >= Fixed(0)) || (a1 <= Fixed(0) && a2 <= Fixed(0) && a3 <= Fixed(0));
}
