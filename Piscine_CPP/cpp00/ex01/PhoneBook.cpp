/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:24:49 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/25 11:55:17 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : _contactCount(0) {}

PhoneBook::~PhoneBook() {}

void PhoneBook::addContact(const Contact& contact) {
    if (_contactCount >= MAX_CONTACTS) {
        // Décaler les contacts existants vers la droite
        for (int i = MAX_CONTACTS - 1; i > 0; --i) {
            _contacts[i] = _contacts[i - 1];
        }
        _contacts[0] = contact;
    } else {
        // Ajouter le nouveau contact au début
        for (int i = _contactCount; i > 0; --i) {
            _contacts[i] = _contacts[i - 1];
        }
        _contacts[0] = contact;
        ++_contactCount;
    }
}

void PhoneBook::printContacts() const {
	std::cout << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << "|" << std::endl;
    for (int i = 0; i < _contactCount; ++i) {
        std::cout << std::setw(10) << i + 1 << "|"
                  << std::setw(10) << _truncateString(_contacts[i].getFirstName()) << "|"
                  << std::setw(10) << _truncateString(_contacts[i].getLastName()) << "|"
                  << std::setw(10) << _truncateString(_contacts[i].getNickname()) << "|" << std::endl;
	}
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << std::endl;
}

void PhoneBook::searchContact() const {
	if (_contactCount == 0) {
		std::cout << "No contacts available." << std::endl;
		return;
	}
	printContacts();
	std::string ind;
	int index;
    std::cout << "Enter index to display contact: ";
	std::getline(std::cin, ind);
	index = atoi(ind.c_str());
    if (index >= 1 && index <= _contactCount) {
        std::cout << "First Name: " << _contacts[index - 1].getFirstName() << std::endl;
        std::cout << "Last Name: " << _contacts[index - 1].getLastName() << std::endl;
        std::cout << "Nickname: " << _contacts[index - 1].getNickname() << std::endl;
        std::cout << "Phone Number: " << _contacts[index - 1].getPhoneNumber() << std::endl;
        std::cout << "Darkest Secret: " << _contacts[index - 1].getDarkestSecret() << std::endl;
		std::cout << std::endl;
    } else {
        std::cout << "Invalid index." << std::endl;
    }
	
}

std::string PhoneBook::_truncateString(const std::string& str) const {
    const int MAX_LENGTH = 10;
    if (str.length() <= MAX_LENGTH) {
        return str;
    } else {
        return str.substr(0, MAX_LENGTH - 1) + ".";
    }
}
