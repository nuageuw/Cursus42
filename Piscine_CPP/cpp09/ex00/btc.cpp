/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:23:04 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/20 18:49:01 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btc.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {
    std::ifstream file("data.csv");
    if (!file.is_open()) {
        std::cerr << "data.csv: could not open file\n";
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) 
            continue;
        size_t pos = line.find(',');
        if (pos == std::string::npos)
            continue;
        std::string date = line.substr(0, pos);
        float value = std::atof(line.substr(pos + 1).c_str());
        _map.insert(std::make_pair(date, value));
    }
    file.close();
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    this->_map = other._map;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this == &other)
        return *this;

    this->_map = other._map;

    return *this;
}


void BitcoinExchange::process_input(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << filename << ": could not be opened\n";
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        size_t pos = line.find('|');
        if (pos == std::string::npos) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string date = _parse_date(line, pos);
        if (date.empty())
            continue;
        float value = _parse_number(line, pos);
        if (value < 0)
            continue;
        _find_rate(date, value);
    }
    file.close();
}

std::string BitcoinExchange::_parse_date(const std::string& str, size_t pos) {
    size_t lpos = str.find_first_not_of(WHITESPACES);
    size_t rpos = str.find_last_not_of(WHITESPACES, pos - 1);
    if (lpos == pos) {
        std::cout << "Error: bad input => " << str << std::endl;
        return "";
    }
    std::string date = str.substr(lpos, rpos - lpos + 1);
    if (!_valid_date(date)) {
        std::cout << "Error: invalid date format.\n";
        return "";
    }
    return date;
}

float BitcoinExchange::_parse_number(const std::string& str, size_t pos) {
    size_t lpos = str.find_first_not_of(WHITESPACES, pos + 1);
    size_t rpos = str.find_last_not_of(WHITESPACES);
    if (rpos == pos) {
        std::cout << "Error: bad input => " << str << std::endl;
        return -1;
    }
    float value = std::strtof(str.substr(lpos).c_str(), NULL);
    if (errno == ERANGE || !_valid_number(str.substr(lpos, rpos - lpos + 1))) {
        std::cout << "Error: invalid number.\n";
        return -1;
    } else if (value < 0) {
        std::cout << "Error: not a positive number.\n";
        return -1;
    } else if (value > 1000) {
        std::cout << "Error: too large a number.\n";
        return -1;
    }
    return value;
}

bool BitcoinExchange::_valid_date(const std::string& date) {
    if (date.length() != 10)
        return false;

    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            if (day > 29)
                return false;
        } else {
            if (day > 28)
                return false;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30)
            return false;
    }

    return true;
}

bool BitcoinExchange::_valid_number(const std::string& number) {
    int count = 0;
    for (size_t i = 0; i < number.length(); i++) {
        if (!isdigit(number[i]) && number[i] != '.')
            return false;
        if (number[i] == '.')
            count++;
    }
    return count <= 1;
}

void BitcoinExchange::_find_rate(const std::string& date, float value) {
    std::map<std::string, float>::iterator it = _map.upper_bound(date);
    if (it == this->_map.begin()) {
        std::cout << date << " => no data available.\n";
        return;
    }
    it--;
    std::cout << date << " => " << value << " = " << value * it->second << std::endl;
}