/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:17:45 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 11:24:16 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    try {
        // Bureaucrat bureaucrat("Alice", 0); // Should throw GradeTooHighException

        // Bureaucrat bureaucrat("Bob", 160); // Should throw GradeTooLowException

        // Form form1("Form1", 0, 30); // Should throw GradeTooHighException

        // Form form2("Form2", 160, 30); // Should throw GradeTooLowException

        // Form form3("Form3", 40, 0); // Should throw GradeTooHighException

        // Form form4("Form4", 40, 160); // Should throw GradeTooLowException

        
        Bureaucrat bureaucrat("John", 50);

        Form taxForm("Tax Form", 40, 30);
        Form propertyForm("Property Form", 60, 70);

        std::cout << "Initial state:\n";
        std::cout << bureaucrat;
        std::cout << taxForm;
        std::cout << propertyForm;

        std::cout << "\nAttempting to sign forms:\n";
        bureaucrat.signForm(taxForm); // Should fail
        bureaucrat.signForm(propertyForm); // Should succeed

        std::cout << "\nFinal state after signing attempts:\n";
        std::cout << taxForm;
        std::cout << propertyForm;

        std::cout << "\nTesting grade increment and decrement:\n";
        bureaucrat.incrementGrade(); // Grade becomes 49
        std::cout << "Bureaucrat after increment: " << bureaucrat;
        bureaucrat.decrementGrade(); // Grade becomes 50
        std::cout << "Bureaucrat after decrement: " << bureaucrat;

    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}