/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:52:52 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 17:52:53 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class Animal {
public:
    virtual ~Animal() {} // Ajout d'un destructeur virtuel
    virtual void makeSound() const = 0; // Fonction virtuelle pure
    virtual const std::string &getType() const = 0; // Fonction virtuelle pure
};

#endif
