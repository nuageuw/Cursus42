/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:49:42 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 00:28:49 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"


int main() {
    Animal *animals[4];
    for (int i = 0; i < 2; i++)
        animals[i] = new Dog();
    for (int i = 2; i < 4; i++)
        animals[i] = new Cat();
    for (int i = 0; i < 4; i++)
        delete animals[i];

    {
        Cat cat1;
        cat1.setIdea("Yes MA BOI");
        Cat cat2(cat1);
        cat1.setIdea("YupYup");

        std::cout << "Shallow Copy Test:" << std::endl;
        std::cout << "Cat1 Idea 1: " << cat1.getIdea(0) << std::endl;
        std::cout << "Cat1 Idea 2: " << cat1.getIdea(1) << std::endl;
        std::cout << "Cat2 Idea 1: " << cat2.getIdea(0) << std::endl;
        std::cout << "Cat2 Idea 2: " << cat2.getIdea(1) << std::endl;
    }

	{
		Cat cat1;
		cat1.setIdea("Nah");
		Cat cat2 = cat1;
		cat1.setIdea("blblblblblb");
	
		std::cout << "\nDeep Copy Test:" << std::endl;
		std::cout << "Cat1 Idea 1: " << cat1.getIdea(0) << std::endl;
		std::cout << "Cat1 Idea 2: " << cat1.getIdea(1) << std::endl;
		std::cout << "Cat2 Idea 1: " << cat2.getIdea(0) << std::endl;
		std::cout << "Cat2 Idea 2: " << cat2.getIdea(1) << std::endl;
	}

    return 0;
}