/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:17:45 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 10:43:45 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main() {
	// Test for copy constructor and assignment operator
	// Bureaucrat test_1("Test_1", 100);
    // std::cout << test_1 << std::endl;

    // Bureaucrat shallow(test_1);
    // std::cout << shallow << std::endl;

    // Bureaucrat def;
    // def = test_1;
    // std::cout << def << std::endl;
    try {
        Bureaucrat bureaucrat("John", 149);
        std::cout << bureaucrat;

        bureaucrat.incrementGrade();
        std::cout << bureaucrat;

        bureaucrat.decrementGrade();
        std::cout << bureaucrat;

        bureaucrat.decrementGrade(); // should throw GradeTooLowException
		std::cout << bureaucrat; // Not reached
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
	try {
		Bureaucrat failure_guy("John", 0);  // should throw TooHighException
        Bureaucrat failure_guy_2("John", 70000);  // Not reached
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}