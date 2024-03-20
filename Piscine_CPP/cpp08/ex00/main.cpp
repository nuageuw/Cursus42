/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:54:03 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/20 18:34:46 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>

int main() {
    std::vector<int> vec;
    for (int i = 1; i <= 5; ++i) {
        vec.push_back(i);
    }
    try {
        std::vector<int>::iterator result = easyFind(vec, 3);
        std::cout << "Value found at index: " << std::distance(vec.begin(), result) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    std::list<int> lst;
    for (int i = 6; i <= 10; ++i) {
        lst.push_back(i);
    }
    try {
        std::list<int>::iterator result = easyFind(lst, 7);
        std::cout << "Value found at index: " << std::distance(lst.begin(), result) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}