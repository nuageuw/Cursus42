/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:25:27 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 09:35:21 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <iostream>
#include <exception>

template <typename T>
class Array {
private:
    T* elements;
    unsigned int length;

public:
    Array() : elements(0), length(0) {}

    explicit Array(unsigned int n) : length(n) {
        elements = new T[length];
        for (unsigned int i = 0; i < length; ++i) {
            elements[i] = T();
        }
    }

    Array(const Array& other) : length(other.length) {
        elements = new T[length];
        for (unsigned int i = 0; i < length; ++i) {
            elements[i] = other.elements[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] elements;

            length = other.length;
            elements = new T[length];
            for (unsigned int i = 0; i < length; ++i) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    ~Array() {
        delete[] elements;
    }

    T& operator[](unsigned int index) {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }

    unsigned int size() const {
        return length;
    }
};

#endif