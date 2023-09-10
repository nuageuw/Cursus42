/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:43:39 by aburnott          #+#    #+#             */
/*   Updated: 2023/06/20 12:54:46 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(std::string name) : _name(name) {
	std::cout << _name << " is created" << std::endl;
}

Zombie::~Zombie() {
	std::cout << _name << " is destroyed" << std::endl;
}

void Zombie::announce() const {
	std::cout << _name << " BraiiiiiiinnnzzzZ..." << std::endl;
}