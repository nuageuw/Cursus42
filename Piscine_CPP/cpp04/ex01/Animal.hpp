/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:39:02 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/15 23:52:35 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>
#include <iostream>

class Animal {
    public:
        Animal();
        Animal(const Animal &other);
        virtual ~Animal();

        Animal &operator=(const Animal &other);

        std::string getType() const;
        virtual void makeSound() const;
        
    protected:
        std::string _type;
};

#endif 
