/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:40:28 by aburnott          #+#    #+#             */
/*   Updated: 2023/08/28 15:41:41 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <string>
#include <iostream>

class WrongAnimal {
protected:
    std::string _type;

public:
    WrongAnimal();
    virtual ~WrongAnimal();
    void makeSound() const;
    std::string getType() const;
};

#endif /* WRONGANIMAL_HPP */
