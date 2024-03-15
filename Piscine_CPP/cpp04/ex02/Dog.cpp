/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:46:10 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 00:39:08 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : AAnimal() {
    std::cout << "Dog constructor called" << std::endl;
    this->_type = "Dog";
    this->_brain = new Brain();
}

Dog::Dog(const Dog &other) : AAnimal(other) {
    std::cout << "Dog copy constructor called" << std::endl;
    this->_type = other._type;
    this->_brain = new Brain(*other._brain);
}

Dog &Dog::operator=(const Dog &other) {
    std::cout << "Dog assignation operator called" << std::endl;
    if (this != &other) {
        this->_type = other._type;
        *(this->_brain) = (*other._brain);
    }
    return *this;
}

Dog::~Dog() {
    std::cout << "Dog destructor called" << std::endl;
    delete this->_brain;
}

void Dog::makeSound() const {
    std::cout << "Woof Woof!" << std::endl;
}
