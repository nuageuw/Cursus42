/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:39:02 by aburnott          #+#    #+#             */
/*   Updated: 2023/08/28 15:41:20 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>
#include <iostream>

class Animal {
public:
    Animal();
    virtual ~Animal();
    virtual void makeSound() const;
    std::string getType() const;

protected:
    std::string _type;
};

#endif /* ANIMAL_HPP */
