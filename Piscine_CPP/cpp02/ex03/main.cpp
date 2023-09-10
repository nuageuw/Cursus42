/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:40:42 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 16:42:31 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"
#include "Point.hpp"

int main() {
	bool bsp(Point const a, Point const b, Point const c, Point const point);
    Point a(0, 0);
    Point b(4, 0);
    Point c(2, 3);

    Point p1(2, 1); // Point inside the triangle
    Point p2(2, 5); // Point outside the triangle

    bool result1 = bsp(a, b, c, p1);
    bool result2 = bsp(a, b, c, p2);

    std::cout << "Point p1 is inside the triangle: " << std::boolalpha << result1 << std::endl;
    std::cout << "Point p2 is inside the triangle: " << std::boolalpha << result2 << std::endl;

    return 0;
}
