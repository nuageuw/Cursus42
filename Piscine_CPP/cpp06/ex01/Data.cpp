/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:33:54 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 00:06:49 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

Data::Data() {}

Data::Data(int value) : m_value(value) {}

Data::~Data() {}

Data::Data(Data const &other) {
	(void)other;
	return;
}

Data &Data::operator=(const Data assign) {
	(void)assign;
	return *this;
}

int Data::getValue() const {
	return m_value;
}