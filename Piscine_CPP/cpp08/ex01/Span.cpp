/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:06:25 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 10:24:20 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
# include <list>
# include <iostream>
# include <cstdlib>
# include <algorithm>
# include <numeric>


Span::Span(unsigned int N) : maxSize(N) {}

Span::Span(const Span& other) : maxSize(other.maxSize), numbers(other.numbers) {
	*this = other;
}

Span::~Span() {}

Span	&Span::operator=(const Span &copy)
{
	this->numbers = copy.numbers;

	return *this;
}

void Span::addNumber(int num) {
    if (numbers.size() >= maxSize) {
        throw std::runtime_error("Cannot add more numbers, Span is full");
    }
    numbers.push_back(num);
}


int Span::shortestSpan() {
	if (numbers.size() <= 1) {
		throw std::runtime_error("Cannot find span, not enough numbers stored");
	}
	std::sort(numbers.begin(), numbers.end());
	std::vector<int> differences(numbers.size() - 1);
	std::adjacent_difference(numbers.begin(), numbers.end(), differences.begin());
	return *std::min_element(differences.begin() + 1, differences.end());
}

int Span::longestSpan() {
	if (numbers.size() <= 1) {
		throw std::runtime_error("Cannot find span, not enough numbers stored");
	}
	return *std::max_element(numbers.begin(), numbers.end()) - *std::min_element(numbers.begin(), numbers.end());
}

void Span::addNumbers(std::vector<int>& nums) {
    if (numbers.size() + nums.size() > maxSize) {
        throw std::runtime_error("Cannot add more numbers, Span will exceed its size");
    }
    numbers.insert(numbers.end(), nums.begin(), nums.end());
}

std::vector<int> Span::getNumbers() const {
    return numbers;
}

std::ostream& operator<<(std::ostream& os, const Span& span) {
    os << "Span with " << span.getNumbers().size() << " numbers: ";
    for (size_t i = 0; i < span.getNumbers().size(); ++i) {
        os << span.getNumbers()[i];
        if (i != span.getNumbers().size() - 1) {
            os << ", ";
        }
    }
    return os;
}