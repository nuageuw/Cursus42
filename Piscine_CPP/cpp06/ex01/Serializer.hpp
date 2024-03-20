/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:25:20 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/20 18:23:36 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Data.hpp"
#include <stdint.h>

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

class Serializer {
	private:
		Serializer();
		Serializer(Serializer const &other);
		Serializer &operator=(const Serializer assign);
	public:
		~Serializer();

		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);
};

#endif
