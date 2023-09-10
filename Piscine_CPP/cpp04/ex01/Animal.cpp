/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:48:15 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 17:48:17 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : type("Animal") {}

Animal::Animal(const std::string &type) : type(type) {}

Animal::Animal(const Animal &other) : type(other.type) {}

Animal &Animal::operator=(const Animal &other) {
    if (this != &other) {
        type = other.type;
    }
    return *this;
}

Animal::~Animal() {}

const std::string &Animal::getType() const {
    return type;
}

void Animal::makeSound() const {
    std::cout << "Animal sound!" << std::endl;
}
