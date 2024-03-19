/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:06:22 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 22:09:59 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include <cstring>

RPNCalculator::RPNCalculator() {}

RPNCalculator::RPNCalculator(const RPNCalculator& other) {
	(void)other;
}

RPNCalculator::~RPNCalculator() {}

RPNCalculator& RPNCalculator::operator=(const RPNCalculator& other) {
    (void)other;
    return *this;
}

int RPNCalculator::evaluate(const std::string& expression) {
    std::istringstream iss(expression);
    std::stack<int> operands;
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            operands.push(std::atoi(token.c_str()));
	} else if (token.size() == 1 && strchr("+-*/", token[0])) {
            if (operands.size() < 2) {
                throw std::runtime_error("Error: insufficient operands for operation.");
            }
            int op2 = operands.top();
            operands.pop();
            int op1 = operands.top();
            operands.pop();
            switch (token[0]) {
                case '+':
                    operands.push(op1 + op2);
                    break;
                case '-':
                    operands.push(op1 - op2);
                    break;
                case '*':
                    operands.push(op1 * op2);
                    break;
                case '/':
                    if (op2 == 0) {
                        throw std::runtime_error("Error: division by zero.");
                    }
                    operands.push(op1 / op2);
                    break;
            }
        } else {
            throw std::runtime_error("Error: invalid token.");
        }
    }

    if (operands.size() != 1) {
        throw std::runtime_error("Error: invalid expression.");
    }

    return operands.top();
}