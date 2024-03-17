/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:17:45 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 20:34:33 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
    Bureaucrat bigBoss("Zen", 1);
    Bureaucrat employe1("Vatira", 139);
    Bureaucrat employe2("Juicy", 50);
    Bureaucrat employe3("Atow", 20);
    std::cout << "===========Copy and assigment operators==========" << std::endl;
    ShrubberyCreationForm def;
    std::cout << def;
    std::cout << def.getTarget() << std::endl;
    ShrubberyCreationForm test("House");
    std::cout << test;
    std::cout << test.getTarget() << std::endl;
    ShrubberyCreationForm test2(test);
    std::cout << test2;
    std::cout << test2.getTarget() << std::endl;
    ShrubberyCreationForm test3;
    test3 = test2;
    std::cout << test3;
    std::cout << test3.getTarget() << std::endl;
    std::cout << "================SHRUB============================" << std::endl;
    std::cout << test;
    std::cout << test.getTarget() << std::endl;
    employe1.executeForm(test);
    bigBoss.executeForm(test);
    employe1.signForm(test);
    employe1.executeForm(test);
    bigBoss.executeForm(test);
    std::cout << "================ROBOTOMY============================" << std::endl;
    RobotomyRequestForm robot("Michel");
    std::cout << robot;
    std::cout << robot.getTarget() << std::endl;
    employe2.executeForm(robot);
    bigBoss.executeForm(robot);
    employe2.signForm(robot);
    bigBoss.signForm(robot);
    employe2.executeForm(robot);
    bigBoss.executeForm(robot);
    std::cout << "================PRESIDENT============================" << std::endl;
    PresidentialPardonForm prisoner("Robert");
    std::cout << prisoner;
    std::cout << prisoner.getTarget() << std::endl;
    //prisoner.execute(bigBoss); ->will crash if not in try catch block !
    employe3.executeForm(prisoner);
    bigBoss.executeForm(prisoner);
    employe3.signForm(prisoner);
    bigBoss.signForm(prisoner);
    employe3.executeForm(prisoner);
    bigBoss.executeForm(prisoner);
    //debug
}