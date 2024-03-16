/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:38:52 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 13:57:49 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm {
private:
    const std::string _name;
    std::string _target;
    bool _signedStatus;
    const int _gradeToSign;
    const int _gradeToExecute;

public:
    class GradeTooHighException : public std::exception {
    public:
        GradeTooHighException() throw() {}
        virtual const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        GradeTooLowException() throw() {}
        virtual const char* what() const throw();
    };

    AForm();
    AForm(const std::string& name, int gradeToSign, int gradeToExecute, const std::string& target);
    virtual ~AForm();
    AForm(const AForm& other);
    AForm& operator=(const AForm& other);
    
    const std::string& getName() const;
    bool isSigned() const;
    int getGradeToSign() const;
    int getGradeToExecute() const;
    virtual void execute(const Bureaucrat& executor) const = 0;
    void beSigned(const Bureaucrat& bureaucrat);
    std::string getTarget(void) const;
};

std::ostream& operator<<(std::ostream& os, const AForm& form);

#endif
