/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConversion.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:08:27 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/17 01:30:35 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConversion.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdlib> // For strtol and strtof

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

#include <cmath> // For std::isnan

void ScalarConversion::convert(std::string str)
{
    try
    {
        if (str.size() == 1)
        {
            _convertChar(str);
        }
        else if (_isInteger(str))
        {
            _convertInteger(str);
        }
        else if (_isFloat(str) || str == "nan" || str == "-inff" || str == "+inff")
        {
            _convertFloat(str);
        }
        else if (_isDouble(str) || str == "nan" || str == "-inf" || str == "+inf")
        {
            _convertDouble(str);
        }
        else
        {
            throw std::invalid_argument("Invalid input: not a valid scalar value.");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void ScalarConversion::_convertChar(const std::string& str)
{
    char c = str[0];
    int i = static_cast<int>(c);
    float f = static_cast<float>(c);
    double d = static_cast<double>(c);

    std::cout << "Char: ";
    if (!std::isprint(c))
    {
        std::cout << "Non displayable" << std::endl;
    }
    else
    {
        std::cout << c << std::endl;
    }
    std::cout << "Int: " << i << std::endl;
    std::cout << "Float: " << f << "f" << std::endl;
    std::cout << "Double: " << d << std::endl;
}

void ScalarConversion::_convertInteger(const std::string& str)
{
    char* endPtr;
    long value = std::strtol(str.c_str(), &endPtr, 10);
    if (*endPtr != '\0')
    {
        throw std::invalid_argument("Invalid input");
    }

    char c = static_cast<char>(value);
    float f = static_cast<float>(value);
    double d = static_cast<double>(value);

    std::cout << "Char: ";
    if (!std::isprint(c))
    {
        std::cout << "Non displayable" << std::endl;
    }
    else
    {
        std::cout << c << std::endl;
    }
    std::cout << "Int: " << value << std::endl;
    std::cout << "Float: " << f << "f" << std::endl;
    std::cout << "Double: " << d << std::endl;
}

void ScalarConversion::_convertFloat(const std::string& str)
{
    char* endPtr;
    float value = std::strtof(str.c_str(), &endPtr);
    if (*endPtr != '\0')
    {
        throw std::invalid_argument("Invalid input");
    }

    char c = static_cast<char>(value);
    int i = static_cast<int>(value);
    double d = static_cast<double>(value);

    std::cout << "Char: ";
    if (!std::isprint(c))
    {
        std::cout << "Non displayable" << std::endl;
    }
    else
    {
        std::cout << c << std::endl;
    }
    std::cout << "Int: " << i << std::endl;
    std::cout << "Float: " << value << "f" << std::endl;
    std::cout << "Double: " << d << std::endl;
}

void ScalarConversion::_convertDouble(const std::string& str)
{
    std::istringstream iss(str);
    double value;
    if (!(iss >> value))
    {
        throw std::invalid_argument("Invalid input");
    }

    char c = static_cast<char>(value);
    int i = static_cast<int>(value);
    float f = static_cast<float>(value);

    std::cout << "Char: ";
    if (!std::isprint(c))
    {
        std::cout << "Non displayable" << std::endl;
    }
    else
    {
        std::cout << c << std::endl;
    }
    std::cout << "Int: " << i << std::endl;
    std::cout << "Float: " << f << "f" << std::endl;
    std::cout << "Double: " << value << std::endl;
}

bool ScalarConversion::_isInteger(const std::string& str)
{
    if (str.empty())
    {
        return false;
    }

    size_t start = 0;
    if (str[0] == '+' || str[0] == '-')
    {
        start = 1;
    }

    for (size_t i = start; i < str.size(); i++)
    {
        if (!std::isdigit(str[i]))
        {
            return false;
        }
    }

    return true;
}

bool ScalarConversion::_isFloat(const std::string& str)
{
    if (str.empty())
    {
        return false;
    }

    size_t start = 0;
    if (str[0] == '+' || str[0] == '-')
    {
        start = 1;
    }

    bool dotFound = false;
    for (size_t i = start; i < str.size(); i++)
    {
        if (str[i] == '.')
        {
            if (dotFound)
            {
                return false;
            }
            dotFound = true;
        }
        else if (!std::isdigit(str[i]))
        {
            return false;
        }
    }

    if (dotFound && (start == str.size() - 1 || str.size() == 1))
    {
        return false;
    }

    return true;
}

bool ScalarConversion::_isDouble(const std::string& str)
{
    if (str.empty())
    {
        return false;
    }

    size_t start = 0;
    if (str[0] == '+' || str[0] == '-')
    {
        start = 1;
    }

    bool dotFound = false;
    for (size_t i = start; i < str.size(); i++)
    {
        if (str[i] == '.')
        {
            if (dotFound)
            {
                return false;
            }
            dotFound = true;
        }
        else if (!std::isdigit(str[i]))
        {
            return false;
        }
    }

    if (dotFound && (start == str.size() - 1 || str.size() == 1))
    {
        return false;
    }

    return true;
}
