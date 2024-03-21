/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:15:34 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/21 18:19:09 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern &copy)
{
	(void) copy;
}

Intern::~Intern()
{
}

Intern	&Intern::operator=(const Intern &copy)
{
	(void) copy;

	return *this;
}

AForm	*Intern::makeForm(const std::string &name, const std::string &target)
{
	std::string	names[] = {"shrubbery creation", "robotomy request", "presidential pardon"};
	int	i = 0;

	while (i < 3 && names[i] != name)
		i++;

	switch (i)
	{
		case 0:
			return new ShrubberyCreationForm(target);
		case 1:
			return new RobotomyRequestForm(target);
		case 2:
			return new PresidentialPardonForm(target);
		default:
			throw Intern::UnknownFormException();
	}
}

const char	*Intern::UnknownFormException::what() const throw()
{
	return ("Unknown form.");
}