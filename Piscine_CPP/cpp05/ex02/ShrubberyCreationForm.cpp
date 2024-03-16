/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:41:15 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 12:30:22 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include <fstream>
#include <cstdlib>

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("Shrubbery Creation Form", 145, 137), _target("") {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) : AForm(other), _target(other._target) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
	if (this != &other) {
		this->_target = other._target;
	}
	return *this;
}

const std::string& ShrubberyCreationForm::getTarget() const {
	return _target;
}

// void ShrubberyCreationForm::setTarget(const std::string& target) {
// 	_target = target;
// }

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("Shrubbery Creation Form", 145, 137), _target(target) {}

void ShrubberyCreationForm::execute(const Bureaucrat& executor) const {
	if (!isSigned())
		throw AForm::GradeTooLowException();
	if (executor.getGrade() > getGradeToExecute())
		throw AForm::GradeTooLowException();
	
	std::ofstream output((this->getTarget() + "_shrubbery").c_str());
	if (!output.is_open())
		throw Failed();
	
	output << "ASCII trees for " << this->_target << "!\n";
	output.close();
}

const char* ShrubberyCreationForm::Failed::what(void) const throw() {
	return "Failed to create file";
}
