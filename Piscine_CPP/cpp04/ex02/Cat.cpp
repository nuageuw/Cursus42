/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:46:29 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 00:38:52 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : AAnimal() {
    std::cout << "Cat constructor called" << std::endl;
    this->_type = "Cat";
    this->_brain = new Brain();
}

Cat::Cat(const Cat &other) : AAnimal(other) {
    std::cout << "Cat copy constructor called" << std::endl;
    this->_type = other._type;
    this->_brain = new Brain(*other._brain);
}

Cat &Cat::operator=(const Cat &other) {
    std::cout << "Cat assignation operator called" << std::endl;
    if (this != &other) {
        this->_type = other._type;
        *(this->_brain) = (*other._brain);
    }
    return *this;
}

Cat::~Cat() {
    std::cout << "Cat destructor called" << std::endl;
    delete this->_brain;
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
