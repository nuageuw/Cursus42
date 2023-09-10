/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:41:47 by aburnott          #+#    #+#             */
/*   Updated: 2023/08/28 15:42:57 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound();
    j->makeSound();
    meta->makeSound();

    delete meta;
    delete j;
    delete i;

    std::cout << "\nTesting WrongAnimal and WrongCat:\n" << std::endl;

    const WrongAnimal* wAnimal = new WrongAnimal();
    const WrongAnimal* wCat = new WrongCat();
    std::cout << wAnimal->getType() << " " << std::endl;
    std::cout << wCat->getType() << " " << std::endl;
    wAnimal->makeSound();
    wCat->makeSound();
    delete wAnimal;
    delete wCat;

    return 0;
}
