/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:53:55 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 17:19:51 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    //This line will not compile because AAnimal is an abstract class
    // AAnimal test; 

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
