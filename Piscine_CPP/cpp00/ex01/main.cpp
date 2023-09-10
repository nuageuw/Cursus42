/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:48:25 by aburnott          #+#    #+#             */
/*   Updated: 2023/06/26 11:12:16 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "PhoneBook.hpp"

bool isNumeric(const std::string& str) {
    // Vérifie si tous les caractères de la chaîne sont des chiffres
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    PhoneBook phoneBook;

    while (true) {
		phoneBook.printContacts();
        std::string command;
		
		bool valid_num = false;
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        std::getline(std::cin, command);

        if (command == "ADD") {
            std::string firstName, lastName, nickname, phoneNumber, darkestSecret;
            std::cout << "Enter first name: ";
            std::getline(std::cin, firstName);
            std::cout << "Enter last name: ";
            std::getline(std::cin, lastName);
            std::cout << "Enter nickname: ";
            std::getline(std::cin, nickname);
		    while (!valid_num) {
                std::cout << "Enter phone number: ";
                std::getline(std::cin, phoneNumber);
		    	if (isNumeric(phoneNumber) && phoneNumber.length() == 10) {
		    		valid_num = true;
		    	} else {
		    		phoneNumber = "";
		    		std::cout << "Invalid phone number or must be 10 digits." << std::endl;	
		    	}
   		    }
            std::cout << "Enter darkest secret: ";
			std::getline(std::cin, darkestSecret);
            
            Contact contact(firstName, lastName, nickname, phoneNumber, darkestSecret);
            phoneBook.addContact(contact);
        } else if (command == "SEARCH") {
            phoneBook.searchContact();
        } else if (command == "EXIT") {
            break;
        } else {
            // Ignore command
        }

    }

    return 0;
}
