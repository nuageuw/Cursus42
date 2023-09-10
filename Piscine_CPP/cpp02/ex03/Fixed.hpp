/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:38:46 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 16:38:56 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_H
#define FIXED_H

class Fixed {
public:
    Fixed();
    Fixed(const Fixed &other);
    Fixed(const int intValue);
    Fixed(const float floatValue);
    ~Fixed();

    Fixed &operator=(const Fixed &other);

    int getRawBits() const;
    void setRawBits(const int raw);

    float toFloat() const;
    int toInt() const;

    // Déclaration des opérateurs de comparaison
    bool operator>(const Fixed &other) const;
    bool operator<(const Fixed &other) const;
    bool operator>=(const Fixed &other) const;
    bool operator<=(const Fixed &other) const;
    bool operator==(const Fixed &other) const;
    bool operator!=(const Fixed &other) const;

    // Déclaration des opérateurs d'arithmétique
    Fixed operator+(const Fixed &other) const;
    Fixed operator-(const Fixed &other) const;
    Fixed operator*(const Fixed &other) const;
    Fixed operator/(const Fixed &other) const;

    // Déclaration des opérateurs d'incrémentation et de décrémentation
    Fixed &operator++(); // Pré-incrémentation
    Fixed operator++(int); // Post-incrémentation
    Fixed &operator--(); // Pré-décrémentation
    Fixed operator--(int); // Post-décrémentation

    static Fixed &min(Fixed &a, Fixed &b);
    static const Fixed &min(const Fixed &a, const Fixed &b);
    static Fixed &max(Fixed &a, Fixed &b);
    static const Fixed &max(const Fixed &a, const Fixed &b);

private:
    int value;
    static const int fractionalBits;
};

#endif
