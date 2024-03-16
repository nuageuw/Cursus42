/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:49:42 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 17:18:21 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"


int main() {
    // SHOWING ORDER OF CONSTRUCTOR DESTRUCTOR
    Animal *animals[4];
    for (int i = 0; i < 2; i++)
        animals[i] = new Dog();
    for (int i = 2; i < 4; i++)
        animals[i] = new Cat();
    for (int i = 0; i < 4; i++)
        delete animals[i];

	{
		Cat cat1;
		cat1.setIdea("Nah");
		Cat cat2 = cat1;
		cat1.setIdea("blblblblblb");
        Cat cat3(cat1);
        cat3.setIdea("I think I'm hungry");
	
		std::cout << "\nDeep Copy Test:" << std::endl;
		std::cout << "Cat1 Idea 1: " << cat1.getIdea(0) << std::endl;
		std::cout << "Cat1 Idea 2: " << cat1.getIdea(1) << std::endl;
		std::cout << "Cat2 Idea 1: " << cat2.getIdea(0) << std::endl;
		std::cout << "Cat2 Idea 2: " << cat2.getIdea(1) << std::endl;
        std::cout << "Cat3 Idea 1: " << cat3.getIdea(0) << std::endl;
        std::cout << "Cat3 Idea 2: " << cat3.getIdea(1) << std::endl;
        std::cout << "Cat3 Idea 3: " << cat3.getIdea(2) << std::endl;
        cat2.setIdea("AS YOU CAN SEE I HAVE MY OWN IDEAS");
        std::cout << "Cat2 Idea 2: " << cat2.getIdea(1) << std::endl;
        std::cout << "Cat1 Idea 2: " << cat1.getIdea(1) << std::endl; // No change applied on cat1
        std::cout << std::endl;
	}

    return 0;
}