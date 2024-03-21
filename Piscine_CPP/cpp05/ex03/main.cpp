/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:17:45 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/21 18:21:29 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "AForm.hpp"
#include <iostream>

int main()
{
	try
	{
		std::cout << "--- TEST 1 ---\n";
		Bureaucrat	mich("GentleMates", 150);
		std::cout << mich << std::endl;

		Intern	i;
		AForm	*f1 = i.makeForm("bruh :)", "some target");

		delete f1;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	
	try
	{
		std::cout << "\n--- TEST 2 ---\n";
		Bureaucrat	mich("Vitality", 137);
		std::cout << mich << std::endl;

		Intern	i;
		AForm	*f1 = i.makeForm("shrubbery creation", "Zen");

		std::cout << *f1 << std::endl;
		mich.signForm(*f1);
		std::cout << *f1 << std::endl;
		mich.executeForm(*f1);

		delete f1;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}