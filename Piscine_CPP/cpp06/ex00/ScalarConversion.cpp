/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConversion.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:08:27 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/17 22:33:05 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConversion.hpp"

#include <cmath> // For std::isnan
#include <iostream>
#include <string>
#include <cctype> // For isprint
#include <cstdlib> // For atoi and atof
#include <sstream> // For std::ostringstream

ScalarConversion::ScalarConversion()
{
}

ScalarConversion::~ScalarConversion()
{
}

ScalarConversion::ScalarConversion(const ScalarConversion& other)
{
    (void)other;
}

ScalarConversion& ScalarConversion::operator=(const ScalarConversion& other)
{
    (void)other;
    return (*this);
}

void ScalarConversion::convert(std::string str) {
    // Convert to char
    try {
        int intValue = std::atoi(str.c_str());
        char charValue = static_cast<char>(intValue);
        if (std::isprint(charValue)) {
            std::cout << "char: '" << charValue << "'" << std::endl;
        } else {
            std::cout << "char: Non displayable" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "char: impossible" << std::endl;
    }
    // Convert to int
    try {
        int intValue = static_cast<int>(std::atoi(str.c_str()));
        std::cout << "int: " << intValue << std::endl;
    } catch (const std::exception& e) {
        std::cout << "int: impossible" << std::endl;
    }
    // Convert to float
    try {
        float floatValue = static_cast<float>(std::atof(str.c_str()));
        std::ostringstream oss;
        oss << std::fixed;
    
        oss << floatValue;
    
        std::string output = oss.str();
        size_t pos = output.find_last_not_of('0');
        if (pos != std::string::npos && output[pos] == '.') {
            pos++; // Include the decimal point if it's the last character
        }
        output = output.substr(0, pos + 1);
        
        std::cout << "float: " << output << "f" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "float: impossible" << std::endl;
    }
    // Convert to double
    try {
        double doubleValue = static_cast<double>(std::atof(str.c_str()));
        std::ostringstream oss;
        oss << std::fixed;
        oss << doubleValue;
        
        std::string output = oss.str();
        size_t pos = output.find_last_not_of('0');
        if (pos != std::string::npos && output[pos] == '.') {
            pos++; // Include the decimal point if it's the last character
        }
        output = output.substr(0, pos + 1);
        
        std::cout << "double: " << output << std::endl;
    } catch (const std::exception& e) {
        std::cout << "double: impossible" << std::endl;
    }
}
