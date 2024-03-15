/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:53:55 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 00:40:28 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {

    // AAnimal test; This line will not compile because AAnimal is an abstract class

    const AAnimal* animal = new Dog();
    animal->makeSound();
    delete animal;

    const AAnimal* dog = new Dog();
    dog->makeSound();
    delete dog;

    const AAnimal* cat = new Cat();
    cat->makeSound();
    delete cat;

    return 0;
}
