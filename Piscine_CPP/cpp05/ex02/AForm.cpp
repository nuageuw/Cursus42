/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:38:47 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 13:58:54 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm() : _name("AForm"), _signedStatus(false), _gradeToSign(1), _gradeToExecute(1) {}


AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute, const std::string& target)
    : _name(name), _signedStatus(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute), _target(target) {
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    else if (gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
}

AForm::AForm(const AForm& other) : _name(other._name), _signedStatus(other._signedStatus),
                                    _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {}

AForm::~AForm() {
	std::cout << "Form " << this->getName() << " destroyed.\n";
}

AForm& AForm::operator=(const AForm& other) {
    if (this != &other) {
        this->_signedStatus = other._signedStatus;
    }
    return *this;
}

const std::string& AForm::getName() const {
    return _name;
}

bool AForm::isSigned() const {
    return _signedStatus;
}

int AForm::getGradeToSign() const {
    return _gradeToSign;
}

int AForm::getGradeToExecute() const {
    return _gradeToExecute;
}

void AForm::beSigned(const Bureaucrat& bureaucrat) {
    if (this->_signedStatus)
		return;
    if (bureaucrat.getGrade() <= this->_gradeToSign)
        this->_signedStatus = true;
    else
        throw GradeTooLowException();
}

std::ostream& operator<<(std::ostream& os, const AForm& form) {
    os << "Form: " << form.getName() << ", Grade required to sign: " << form.getGradeToSign() << ", Grade required to execute: " << form.getGradeToExecute() << ", Signed: " << (form.isSigned() ? "Yes" : "No") << "\n";
    return os;
}

std::string AForm::getTarget(void) const {
    return (this->_target);
}

const char *AForm::GradeTooHighException::what() const throw() {
    return ("FORM: Grade is too high");
}

const char *AForm::GradeTooLowException::what() const throw() {
    return ("FORM: Grade is too low");
}
