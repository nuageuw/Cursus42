/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:41:15 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 20:29:57 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include <fstream>
#include <cstdlib>

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("Shrubbery Creation Form", 145, 137) {
	std::cout << "ShrubberyCreationForm constructor called" << std::endl;
	this->setTarget("default");
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) : AForm(other) {
	std::cout << "ShrubberyCreationForm copy constructor called" << std::endl;
	*this = other;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
	std::cout << "ShrubberyCreationForm assignation operator called" << std::endl;
	if (this != &other) {
		this->setTarget(other.getTarget());
	}
	return *this;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) : AForm("Shrubbery Creation Form", 145, 137) {
	std::cout << "ShrubberyCreationForm constructor called" << std::endl;
	this->setTarget(target);
}

void ShrubberyCreationForm::execute(const Bureaucrat& executor) const {
	this->AForm::execute(executor);
	
	std::ofstream output((this->getTarget() + "_shrubbery").c_str());
	if (!output.is_open())
		throw std::ofstream::failure("Bad open");
	
	output << "ASCII trees for " << this->getTarget() << "!\n";
	output << "      /\\      \n";
	output << "     /\\*\\     \n";
	output << "    /\\O\\*\\    \n";
	output << "   /*/\\/\\/\\   \n";
	output << "  /\\O\\/\\*\\/\\  \n";
	output << " /\\*\\/\\*\\/\\/\\ \n";
	output << "/\\O\\/\\/*/\\/O/\\ \n";
	output << "      ||      \n";
	output << "      ||      \n";
	output << "      ||      \n";
	output.close();
}
