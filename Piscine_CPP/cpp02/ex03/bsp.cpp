/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:40:05 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 16:40:07 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"
#include <iostream>

bool bsp(Point const a, Point const b, Point const c, Point const point) {
    Fixed const a1 = Fixed(b.getY() - a.getY()) * Fixed(point.getX() - a.getX()) - Fixed(b.getX() - a.getX()) * Fixed(point.getY() - a.getY());
    Fixed const a2 = Fixed(c.getY() - b.getY()) * Fixed(point.getX() - b.getX()) - Fixed(c.getX() - b.getX()) * Fixed(point.getY() - b.getY());
    Fixed const a3 = Fixed(a.getY() - c.getY()) * Fixed(point.getX() - c.getX()) - Fixed(a.getX() - c.getX()) * Fixed(point.getY() - c.getY());

    return (a1 >= Fixed(0) & &a2 >= Fixed(0) & &a3 >= Fixed(0)) || (a1 <= Fixed(0) & &a2 <= Fixed(0) && a3 <= Fixed(0));
}
