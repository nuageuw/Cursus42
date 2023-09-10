/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:24:44 by aburnott          #+#    #+#             */
/*   Updated: 2023/06/19 18:58:21 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact() {}

Contact::Contact(const std::string& firstName, const std::string& lastName, const std::string& nickname,
                 const std::string& phoneNumber, const std::string& darkestSecret)
    : _firstName(firstName),
      _lastName(lastName),
      _nickname(nickname),
      _phoneNumber(phoneNumber),
      _darkestSecret(darkestSecret) {}

Contact::~Contact() {}

std::string Contact::getFirstName() const {
    return _firstName;
}

std::string Contact::getLastName() const {
    return _lastName;
}

std::string Contact::getNickname() const {
    return _nickname;
}

std::string Contact::getPhoneNumber() const {
    return _phoneNumber;
}

std::string Contact::getDarkestSecret() const {
    return _darkestSecret;
}