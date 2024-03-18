/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:21:59 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 09:33:23 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iter.hpp"

int main() {
    int intArray[] = {1, 2, 3, 4, 5};
    char charArray[] = {'a', 'b', 'c', 'd', 'e'};
	std::string	string_array[] = {"This", "is", "RocketLeague", "!"};

    std::cout << "Int array elements: ";
    iter(intArray, 5, print<int>);
    std::cout << std::endl;

    std::cout << "Char array elements: ";
    iter(charArray, 5, print<char>);
    std::cout << std::endl;

	std::cout << "String array elements: ";
	iter(string_array, 4, print<std::string>);
	std::cout << std::endl;

    return 0;
}