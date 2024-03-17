/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:26:11 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 00:39:06 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

Base* generate() {
    int choice = rand() % 3;
    switch(choice) {
        case 0: return new A();
        case 1: return new B();
        case 2: return new C();
    }
    return 0;
}

void identify(Base* p) {
    if (dynamic_cast<A*>(p)) {
        std::cout << "Object type: A" << std::endl;
    } else if (dynamic_cast<B*>(p)) {
        std::cout << "Object type: B" << std::endl;
    } else if (dynamic_cast<C*>(p)) {
        std::cout << "Object type: C" << std::endl;
    } else {
        std::cout << "Unknown object type" << std::endl;
    }
}

void identify(Base& p) {
    try
	{
		A& tryA = dynamic_cast<A&>(p);
		(void)tryA;
		std::cout << "Type: 'A'" << std::endl;
	}
	catch (std::exception &e){}
	try 
	{
		B& tryB = dynamic_cast<B&>(p);
		(void)tryB;
		std::cout << "Type: 'B'" << std::endl;
	}
	catch (std::exception &e){}

	try 
	{
		C& tryC = dynamic_cast<C&>(p);
		(void)tryC;
		std::cout << "Type: 'C'" << std::endl;
	}
	catch (std::exception &e){}
}

int main() {
    srand(time(0));

    Base* obj = generate();
	std::cout << "Identifying object by pointer:" << std::endl;
    identify(obj);
	std::cout << "Identifying object by reference:" << std::endl;
	identify(*obj);

    // Clean up
    delete obj;

    return 0;
}