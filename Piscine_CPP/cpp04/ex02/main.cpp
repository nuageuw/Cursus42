/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:53:55 by aburnott          #+#    #+#             */
/*   Updated: 2023/08/28 15:55:19 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int main() {
    const Animal* animal = new Dog();
    animal->makeSound();
    delete animal;

    const Animal* dog = new Dog();
    dog->makeSound();
    delete dog;

    const Animal* cat = new Cat();
    cat->makeSound();
    delete cat;

    const Animal* wrongCat = new WrongCat();
    wrongCat->makeSound();
    delete wrongCat;

    return 0;
}
