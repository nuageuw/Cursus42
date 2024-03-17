/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:25:20 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 00:16:06 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Data.hpp"
#include <cstdint>

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

class Serializer {
public:

	Serializer();
	~Serializer();
	Serializer(Serializer const &other);
	Serializer &operator=(const Serializer assign);

    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};

#endif
