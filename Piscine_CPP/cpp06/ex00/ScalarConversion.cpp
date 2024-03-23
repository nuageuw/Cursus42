/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConversion.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:03:29 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/23 09:55:20 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConversion.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <cctype>
#include <cerrno>

ScalarConversion::ScalarConversion()
{
}

ScalarConversion::ScalarConversion(const ScalarConversion &copy)
{
    (void) copy;
}

ScalarConversion::~ScalarConversion()
{
}

ScalarConversion& ScalarConversion::operator=(const ScalarConversion &copy)
{
    (void) copy;
    return *this;
}

void ScalarConversion::convert(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
        if (!isprint(str[i]))
        {
            std::cout << "Use of non displayable characters is not allowed\n";
            return;
        }

    if (str.size() == 1 && !isdigit(str[0]))
    {
        _toChar(str);
        return;
    }

    size_t i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (isdigit(str[i]))
        i++;
    if (str[i] == 0)
    {
        _toInt(str);
        return;
    }

    int dot = 0;
    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (isdigit(str[i]) || str[i] == '.')
    {
        if (str[i] == '.')
            dot++;
        i++;
    }
    if (str[i] == 'f' && dot <= 1 && str[i + 1] == 0)
    {
        _toFloat(str);
        return;
    }
    if (str == "-inff" || str == "+inff" || str == "nanf")
    {
        _toFloat(str);
        return;
    }

    dot = 0;
    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (isdigit(str[i]) || str[i] == '.')
    {
        if (str[i] == '.')
            dot++;
        i++;
    }
    if (dot == 1 && str[i] == 0)
    {
        _toDouble(str);
        return;
    }
    if (str == "-inf" || str == "+inf" || str == "nan")
    {
        _toDouble(str);
        return;
    }

    std::cout << "Impossible conversion\nSupported types are <char>, <int>, "
              << "<float> and <double>\n";
}

void ScalarConversion::_toChar(std::string str)
{
    char c = str[0];

    std::cout << "char: '" << c << "'\n";
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "float: " << static_cast<float>(c) << ".0f\n";
    std::cout << "double: " << static_cast<double>(c) << ".0\n";
}

void ScalarConversion::_toInt(std::string str)
{
    std::istringstream iss(str);
    std::istringstream iss2(str);
    int n;
    long l;

    iss >> n;
    iss2 >> l;
    if (n != l)
    {
        std::cout << "char: impossible\n";
        std::cout << "int: overflow\n";
        std::cout << "float: impossible\n";
        std::cout << "double: impossible\n";
        return;
    }
    if (!isprint(static_cast<char>(n)))
        std::cout << "char: non displayable\n";
    else
        std::cout << "char: '" << static_cast<char>(n) << "'\n";
    std::cout << "int: " << n << std::endl;
    std::cout << "float: " << static_cast<float>(n) << ".0f\n";
    std::cout << "double: " << static_cast<double>(n) << ".0\n";
}

void ScalarConversion::_toFloat(std::string str)
{
    float n;

    if (str == "-inff" || str == "+inff" || str == "nanf")
    {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: " << str << std::endl;
        std::cout << "double: " << str.substr(0, str.size() - 1)
                  << std::endl;
        return;
    }
    n = static_cast<float>(strtod(str.c_str(), NULL));
    if (n == HUGE_VALF || n == -HUGE_VALF || errno == ERANGE)
    {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: overflow\n";
        std::cout << "double: impossible\n";
        return;
    }
    if (!isprint(static_cast<char>(n)))
        std::cout << "char: non displayable\n";
    else
        std::cout << "char: '" << static_cast<char>(n) << "'\n";
    std::cout << "int: " << static_cast<int>(n) << std::endl;
    std::cout << "float: " << n;
    if (static_cast<int>(n) == n)
        std::cout << ".0f\n";
    else
        std::cout << "f\n";
    std::cout << "double: " << static_cast<double>(n);
    if (static_cast<int>(n) == n)
        std::cout << ".0";
    std::cout << std::endl;
}

void ScalarConversion::_toDouble(std::string str)
{
    double n;

    if (str == "-inf" || str == "+inf" || str == "nan")
    {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: " << str << "f\n";
        std::cout << "double: " << str << std::endl;
        return;
    }
    n = strtod(str.c_str(), NULL);
    if (n == HUGE_VAL || n == -HUGE_VAL || errno == ERANGE)
    {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: impossible\n";
        std::cout << "double: overflow\n";
        return;
    }
    if (!isprint(static_cast<char>(n)))
        std::cout << "char: non displayable\n";
    else
        std::cout << "char: '" << static_cast<char>(n) << "'\n";
    std::cout << "int: " << static_cast<int>(n) << std::endl;
    std::cout << "float: " << static_cast<float>(n);
    if (static_cast<int>(n) == n)
        std::cout << ".0f\n";
    else
        std::cout << "f\n";
    std::cout << "double: " << n;
    if (static_cast<int>(n) == n)
        std::cout << ".0";
    std::cout << std::endl;
}