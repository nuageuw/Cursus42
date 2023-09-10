/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:46:29 by aburnott          #+#    #+#             */
/*   Updated: 2023/08/28 16:00:34 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal("Cat"), brain(new Brain()) {}

Cat::Cat(const Cat &other) : Animal(other), brain(new Brain(*other.brain)) {}

Cat &Cat::operator=(const Cat &other) {
    if (this != &other) {
        Animal::operator=(other);
        delete brain;
        brain = new Brain(*other.brain);
    }
    return *this;
}

Cat::~Cat() {
    delete brain;
}

void Cat::makeSound() const {
    std::cout << "Meow Meow!" << std::endl;
}

void	Cat::setIdea(const std::string &idea)
{
	this->_brain->setIdea(idea);
}

std::string	Cat::getIdea(unsigned int index) const
{
	return this->_brain->getIdea(index);
	
}
