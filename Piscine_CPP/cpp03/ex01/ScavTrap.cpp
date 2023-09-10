/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:02:29 by aburnott          #+#    #+#             */
/*   Updated: 2023/08/28 15:10:46 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

// Constructeurs et destructeur

ScavTrap::ScavTrap(): ClapTrap()
{
    std::cout << "Default ScavTrap is here, ready for scavenging!" << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name)
{
    this->_hitPoints = 100;
    this->_energyPoints= 50;
    this->_attackDamage = 20;
    std::cout << "ScavTrap " << name << " is here, ready for scavenging!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other) {
    *this = other;
    std::cout << "ScavTrap " << _name << " cloned, ready for scavenging!" << std::endl;
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap " << _name << " is going to rest now." << std::endl;
}

// Fonctions membres

void ScavTrap::attack(const std::string &target) {
    std::cout << "ScavTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << std::endl;
}

void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << _name << " entered Gate keeper mode." << std::endl;
}
