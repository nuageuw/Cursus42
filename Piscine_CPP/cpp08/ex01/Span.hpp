/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:06:19 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 10:20:05 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>

class Span {
private:
    unsigned int maxSize;
    std::vector<int> numbers;

public:
    Span(unsigned int N);
	Span(const Span &copy);
	~Span();
	Span &operator=(const Span &copy);

    void addNumber(int num);

    int shortestSpan();

    int longestSpan();

    void addNumbers(std::vector<int>& nums);
	std::vector<int> getNumbers() const;

};

std::ostream	&operator<<(std::ostream &out, const Span &span);

#endif