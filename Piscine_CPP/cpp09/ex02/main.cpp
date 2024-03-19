/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:18:11 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 22:44:47 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: No input sequence provided." << std::endl;
        return 1;
    }

    std::vector<int> inputSequence;
    for (int i = 1; i < argc; ++i) {
        int num = std::atoi(argv[i]);
        if (num <= 0) {
            std::cerr << "Error: Invalid input sequence." << std::endl;
            return 1;
        }
        inputSequence.push_back(num);
    }

    PmergeMe pmerge(inputSequence);
    pmerge.mergeSortWithVector();
    pmerge.mergeSortWithList();
    pmerge.displayResults();

    return 0;
}
