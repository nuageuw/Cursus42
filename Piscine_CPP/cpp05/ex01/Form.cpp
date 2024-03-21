/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:50:55 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/21 18:06:35 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name("default"), _signedStatus(false), _gradeToSign(150), _gradeToExecute(150) {}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : _name(name), _signedStatus(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
    if (gradeToSign < 1 || gradeToExecute < 1)
	{
        throw GradeTooHighException();
	}
    else if (gradeToSign > 150 || gradeToExecute > 150)
	{
        throw GradeTooLowException();
	}
	std::cout << "Form " << _name << " created.\n";
}

Form::Form(const Form& other) : _name(other._name), _signedStatus(other._signedStatus),
                                _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {}

Form::~Form() {
	std::cout << "Form " << this->getName() << " destroyed.\n";
}

Form& Form::operator=(const Form& other) {
    if (this != &other) {
        this->_signedStatus = other._signedStatus;
    }
    return *this;
}

const std::string& Form::getName() const {
    return _name;
}

bool Form::isSigned() const {
    return _signedStatus;
}

int Form::getGradeToSign() const {
    return _gradeToSign;
}

int Form::getGradeToExecute() const {
    return _gradeToExecute;
}

void Form::beSigned(Bureaucrat& bureaucrat) {
	if (this->_signedStatus)
		return;
    else if (bureaucrat.getGrade() <= this->_gradeToSign)
        this->_signedStatus = true;
    else
        throw GradeTooLowException();
}

std::ostream& operator<<(std::ostream& os, const Form& form) {
    os << "Form: " << form.getName() << ", Grade required to sign: " << form.getGradeToSign() << ", Grade required to execute: " << form.getGradeToExecute() << ", Signed: " << (form.isSigned() ? "Yes" : "No") << "\n";
    return os;
}

const char *Form::GradeTooHighException::what() const throw() {
    return ("FORM: Grade is too high");
}

const char *Form::GradeTooLowException::what() const throw() {
    return ("FORM: Grade is too low");
}