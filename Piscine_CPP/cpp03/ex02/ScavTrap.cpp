/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:02:29 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 17:02:30 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

// Constructeurs et destructeur

ScavTrap::ScavTrap(const std::string &name)
    : name(name), hitPoints(100), energyPoints(50), attackDamage(20) {
    std::cout << "ScavTrap " << name << " is here, ready for scavenging!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other) {
    *this = other;
    std::cout << "ScavTrap " << name << " cloned, ready for scavenging!" << std::endl;
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap " << name << " is going to rest now." << std::endl;
}

// Fonctions membres

void ScavTrap::attack(const std::string &target) {
    std::cout << "ScavTrap " << name << " attacks " << target << ", causing " << attackDamage << " points of damage!" << std::endl;
}

void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << name << " entered Gate keeper mode." << std::endl;
}
