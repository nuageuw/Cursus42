/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:24:51 by aburnott          #+#    #+#             */
/*   Updated: 2023/06/26 11:12:24 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
public:
    static const int MAX_CONTACTS = 8;

    PhoneBook();
    ~PhoneBook();

    void addContact(const Contact& contact);
    void printContacts() const;
    void searchContact() const;

private:
    Contact _contacts[MAX_CONTACTS];
    int _contactCount;

    std::string _truncateString(const std::string& str) const;
};

#endif  // PHONEBOOK_HPP