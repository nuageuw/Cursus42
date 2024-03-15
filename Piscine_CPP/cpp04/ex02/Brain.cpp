/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:45:54 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 00:37:02 by aburnott         ###   ########.fr       */
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

Brain::Brain(const Brain &other) {
    std::cout << "Brain copy constructor Called" << std::endl;
    for (int i = 0; i < 100; i ++) {
        this->_ideas[i] = other._ideas[i];
    }
}

Brain::~Brain() {
    std::cout << "Brain destructor called" << std::endl;
}

Brain &Brain::operator=(const Brain &other) {
    std::cout << "Brain copy operator Called" << std::endl;
    for (int i = 0; i < 100; i ++) {
        this->_ideas[i] = other._ideas[i];
    }
    return (*this);
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
