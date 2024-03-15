/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:52:52 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 00:34:18 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class AAnimal {
    public:
        AAnimal();
        AAnimal(const AAnimal &other);
        virtual ~AAnimal();

        AAnimal &operator=(const AAnimal &other);

        std::string getType() const;
        virtual void makeSound() const = 0;
        
    protected:
        std::string _type;
};

#endif
