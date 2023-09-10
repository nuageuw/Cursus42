/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:39:48 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 16:39:50 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point() : x(0), y(0) {}

Point::Point(const int xValue, const int yValue) : x(xValue), y(yValue) {}

Point::~Point() {}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}
