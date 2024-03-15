/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:39:36 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/15 23:47:50 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() {
    _type = "Dog";
    std::cout << "Dog constructor called" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other) {
    std::cout << "Dog Copy constructor called" << std::endl;
    this->_type = other._type;
}

Dog::~Dog() {
    std::cout << "Dog destructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &other) {
    std::cout << "Dog Assigment operator called" << std::endl;
    if (this != &other)
    {
        this->_type = other._type;
    }
    return (*this);
}

void Dog::makeSound() const {
    std::cout << "Woof Woof!" << std::endl;
}
