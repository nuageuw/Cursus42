/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:42:34 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 20:29:28 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm() : AForm("Robotomy Request Form", 72, 45) {
	std::cout << "RobotomyRequestForm constructor called" << std::endl;
	this->setTarget("default");
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target) : AForm("Robotomy Request Form", 72, 45) {
	std::cout << "RobotomyRequestForm constructor called" << std::endl;
	this->setTarget(target);
}


RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other) : AForm(other) {\
	std::cout << "RobotomyRequestForm copy constructor called" << std::endl;
	*this = other;
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
	std::cout << "RobotomyRequestForm assignation operator called" << std::endl;
	if (this != &other) {
		this->setTarget(other.getTarget());
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {
	std::cout << "RobotomyRequestForm destructor called" << std::endl;
}


void RobotomyRequestForm::execute(const Bureaucrat& executor) const {
    this->AForm::execute(executor);

    std::cout << "BRRRZZZZZZZZZZZZ" << std::endl;
    if (std::rand() % 2 == 0)
		std::cout << this->getTarget() << " has been robotomized\n";
	else
		std::cout << this->getTarget() << " couldn't be robotomized\n";
}
