/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:45:54 by aburnott          #+#    #+#             */
/*   Updated: 2023/08/28 16:02:09 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain() {
    for (int i = 0; i < 100; ++i) {
        _ideas[i] = "Default Idea";
    }
}

Brain::~Brain() {
}

void Brain::setIdea(int index, const std::string &idea) {
    if (index >= 0  &&index < 100) {
        _ideas[index] = idea;
    }
}

const std::string &Brain::getIdea(int index) const {
    static const std::string emptyString;
    if (index >= 0  &&index < 100) {
        return _ideas[index];
    }
    return emptyString;
}
