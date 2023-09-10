/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:39:27 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 16:39:33 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point();
    Point(const int xValue, const int yValue);
    ~Point();

    int getX() const;
    int getY() const;

private:
    int x;
    int y;
};

#endif
