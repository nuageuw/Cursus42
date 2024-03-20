/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:26:15 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/20 18:24:02 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"
#include "Serializer.hpp"
#include <iostream>

int main() {
	
	Data data(42);

    uintptr_t serializedPtr = Serializer::serialize(&data);
	std::cout << "serializedPtr: " << serializedPtr << std::endl;

    Data* deserializedPtr = Serializer::deserialize(serializedPtr);
	std::cout << "deserializedPtr: " << deserializedPtr << std::endl;
	std::cout << "data: " << &data << std::endl;

    if (deserializedPtr == &data) {
        std::cout << "Serialization and deserialization successful. Pointers match." << std::endl;
    } else {
        std::cout << "Serialization and deserialization failed. Pointers do not match." << std::endl;
    }

    return 0;
}

