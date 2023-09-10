/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:25:41 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 16:32:34 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <cmath>

Fixed::Fixed() : fixedPointValue(0) {}

Fixed::Fixed(const int value) {
    fixedPointValue = value << fractionalBits;
}

Fixed::Fixed(const float value) {
    fixedPointValue = roundf(value * (1 << fractionalBits));
}

Fixed::Fixed(const Fixed &other) {
    fixedPointValue = other.fixedPointValue;
}

Fixed::~Fixed() {}

int Fixed::getRawBits() const {
    return fixedPointValue;
}

void Fixed::setRawBits(const int raw) {
    fixedPointValue = raw;
}

float Fixed::toFloat() const {
    return static_cast<float>(fixedPointValue) / (1 << fractionalBits);
}

int Fixed::toInt() const {
    return fixedPointValue >> fractionalBits;
}

Fixed &Fixed::operator=(const Fixed &other) {
    if (this != &other)
        fixedPointValue = other.fixedPointValue;
    return *this;
}

bool Fixed::operator>(const Fixed &other) const {
    return fixedPointValue > other.fixedPointValue;
}

bool Fixed::operator<(const Fixed &other) const {
    return fixedPointValue < other.fixedPointValue;
}

bool Fixed::operator>=(const Fixed &other) const {
    return fixedPointValue >= other.fixedPointValue;
}

bool Fixed::operator<=(const Fixed &other) const {
    return fixedPointValue <= other.fixedPointValue;
}

bool Fixed::operator==(const Fixed &other) const {
    return fixedPointValue == other.fixedPointValue;
}

bool Fixed::operator!=(const Fixed &other) const {
    return fixedPointValue != other.fixedPointValue;
}

Fixed Fixed::operator+(const Fixed &other) const {
    Fixed result;
    result.fixedPointValue = fixedPointValue + other.fixedPointValue;
    return result;
}

Fixed Fixed::operator-(const Fixed &other) const {
    Fixed result;
    result.fixedPointValue = fixedPointValue - other.fixedPointValue;
    return result;
}

Fixed Fixed::operator*(const Fixed &other) const {
    Fixed result;
    result.fixedPointValue = (static_cast<long long>(fixedPointValue) * other.fixedPointValue) >> fractionalBits;
    return result;
}

Fixed Fixed::operator/(const Fixed &other) const {
    Fixed result;
    result.fixedPointValue = (static_cast<long long>(fixedPointValue) << fractionalBits) / other.fixedPointValue;
    return result;
}

Fixed &Fixed::operator++() {
    this->fixedPointValue++;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed tmp(*this);
    this->fixedPointValue++;
    return tmp;
}

Fixed &Fixed::operator--() {
    fixedPointValue -= 1 << fractionalBits;
    return *this;
}

Fixed Fixed::operator--(int) {
    Fixed tmp(*this);
    fixedPointValue -= 1 << fractionalBits;
    return tmp;
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
    return (a < b) ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
    return (a < b) ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
    return (a > b) ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
    return (a > b) ? a : b;
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
    os << static_cast<float>(fixed.getRawBits()) / (1 << 8);
    return os;
}
