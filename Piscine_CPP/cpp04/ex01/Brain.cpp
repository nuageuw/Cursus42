/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reshivii <reshivii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:45:54 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/03 14:53:12 by reshivii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"
#include <iostream>

Brain::Brain() {
    std::cout << "Brain constructor called" << std::endl;
    for (int i = 0; i < 100; ++i) {
        _ideas[i] = "Default Idea";
    }
}

Brain::~Brain() {
    std::cout << "Brain destructor called" << std::endl;
}

void Brain::setIdea(const std::string &idea) {
    for (int i = 0; i < 100; ++i) {
        _ideas[i] = idea;
    }
}

const std::string &Brain::getIdea(int index) const {
    static const std::string emptyString;
    if (index >= 0  &&index < 100) {
        return _ideas[index];
    }
    return emptyString;
}
