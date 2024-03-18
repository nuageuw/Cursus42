/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:14:07 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 10:30:01 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>

int main() {

	{
		// No need to call addNumber 10000 times
		Span	span(10000);

		try
		{
			for (int i = 0; i < 10000; i++)
				span.addNumber(rand() % 10000);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << span << std::endl;
		try
		{
			std::cout << "Shortest span: " << span.shortestSpan() << std::endl;
			std::cout << "Longest span: " << span.longestSpan() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}

    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << sp << std::endl;
	// test of the subject's example
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
    
    std::vector<int> numsToAdd;
    numsToAdd.push_back(1);
    numsToAdd.push_back(2);
    numsToAdd.push_back(3);
    numsToAdd.push_back(4);
    numsToAdd.push_back(5);
    
    try {
        sp.addNumbers(numsToAdd);
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    
    return 0;
}