/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:25:14 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/15 10:23:56 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

Harl::Harl() {
    std::cout << "Harl constructed!" << std::endl;
    std::cout << std::endl;
}

Harl::~Harl() {
    std::cout << "Harl destructed!" << std::endl;
}

void Harl::_debug() {
    std::cout << "[ DEBUG ]" << std::endl;
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
    std::cout << std::endl;
}

void Harl::_info() {
    std::cout << "[ INFO ]" << std::endl;
    std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
    std::cout << std::endl;
}

void Harl::_warning() {
    std::cout << "[ WARNING ]" << std::endl;
    std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << std::endl;
    std::cout << std::endl;
}

void Harl::_error() {
    std::cout << "[ ERROR ]" << std::endl;
    std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
    std::cout << std::endl;
}

void	Harl::complain(std::string level)
{
	std::string	levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	bool found = false;

    for (size_t i = 0; i < 4; i++) {
        if (level == levels[i]) {
            found = true;
        }
        if (found) {
            switch (i) {
                case 0:
                    _debug();
                    break;
                case 1:
                    _info();
                    break;
                case 2:
                   _warning();
                    break;
                case 3:
                    _error();
                    break;
                default:
                    std::cout << "Who asked ?" << std::endl;
                    break;
            }
        }
    }
    if (!found) {
        std::cout << "Who asked ?" << std::endl;
        std::cout << std::endl;
    }
}