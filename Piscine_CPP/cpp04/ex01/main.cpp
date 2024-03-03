/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reshivii <reshivii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:49:42 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/03 14:48:36 by reshivii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
	Animal	*animals[4];

	for (int i = 0; i < 2; i++)
		animals[i] = new Dog();
	for (int i = 2; i < 4; i++)
		animals[i] = new Cat();
	std::cout << std::endl;

	for (int i = 0; i < 4; i++)
		delete animals[i];
	std::cout << std::endl;

	Cat	cat;
	cat.setIdea("This is so boring");
	Cat	copy(cat);
	cat.setIdea("This is sooooooooooooooooo boring");
	std::cout << std::endl;
	
	std::cout << cat.getIdea(0) << std::endl;
	std::cout << cat.getIdea(1) << std::endl;
	std::cout << copy.getIdea(0) << std::endl;
	std::cout << copy.getIdea(1) << std::endl;
	std::cout << std::endl;
	
	return 0;
}
