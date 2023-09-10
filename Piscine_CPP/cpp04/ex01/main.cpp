/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:49:42 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 17:49:44 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    // Test Animal
    std::cout << "--- Test Animal ---" << std::endl;
    const Animal* animal = new Animal();
    animal->makeSound(); // Output: Animal sound!
    std::cout << "Animal type: " << animal->getType() << std::endl; // Output: Animal
    delete animal;

    // Test Dog
    std::cout << "\n--- Test Dog ---" << std::endl;
    const Animal* dog = new Dog();
    dog->makeSound(); // Output: Woof woof!
    std::cout << "Dog type: " << dog->getType() << std::endl; // Output: Dog
    delete dog;

    // Test Cat
    std::cout << "\n--- Test Cat ---" << std::endl;
    const Animal* cat = new Cat();
    cat->makeSound(); // Output: Meow meow!
    std::cout << "Cat type: " << cat->getType() << std::endl; // Output: Cat
    delete cat;

    // Test an array of Animals
    std::cout << "\n--- Test Array of Animals ---" << std::endl;
    const int animalCount = 6;
    const Animal* animals[animalCount];

    animals[0] = new Dog();
    animals[1] = new Cat();
    animals[2] = new Dog();
    animals[3] = new Cat();
    animals[4] = new Dog();
    animals[5] = new Cat();

    for (int i = 0; i < animalCount; i++) {
        const Animal* currentAnimal = animals[i];
        std::cout << "Animal " << i << " type: " << currentAnimal->getType() << std::endl;
        currentAnimal->makeSound();
        delete currentAnimal;
    }

    return 0;
}
