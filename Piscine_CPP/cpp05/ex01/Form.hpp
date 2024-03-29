/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:49:41 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/21 18:06:44 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <stdexcept>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form {
private:
    const std::string _name;
    bool _signedStatus;
    const int _gradeToSign;
    const int _gradeToExecute;

public:
    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw();
    };

	Form();
    Form(const std::string& name, int gradeToSign, int gradeToExecute);
    ~Form();
    Form(const Form& other);
    
    Form& operator=(const Form& other);
    
    const std::string& getName() const;
    bool isSigned() const;
    int getGradeToSign() const;
    int getGradeToExecute() const;
    void beSigned(Bureaucrat& bureaucrat);
};

std::ostream& operator<<(std::ostream& os, const Form& form);

#endif