/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:52:35 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/15 22:12:48 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name("Default"), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "Default ClapTrap is here!" << std::endl;
}

ClapTrap::ClapTrap(const std::string &name)
    : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "ClapTrap " << _name << " is born!" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other) : _name(other._name), _hitPoints(other._hitPoints), 
    _energyPoints(other._energyPoints), _attackDamage(other._attackDamage) {
    std::cout << "ClapTrap " << _name << " has been cloned!" << std::endl;
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap " << _name << " is destroyed!" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
    if (this != &other) {
        this->_name = other._name;
        this->_hitPoints = other._hitPoints;
        this->_energyPoints = other._energyPoints;
        this->_attackDamage = other._attackDamage;
    }
    
    return *this;
}

void ClapTrap::attack(const std::string &target) {
    if (this->_energyPoints == 0) {
        std::cout << "ClapTrap " << this->_name << " is out of energy and can't attack!" << std::endl;
        return;
    }
    if (this->_hitPoints == 0) {
        std::cout << "ClapTrap " << this->_name << " is dead and can't attack!" << std::endl;
        return;
    }
    this->_energyPoints -= 1;
    std::cout << "ClapTrap " << this->_name << " attacks " << target
              << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (this->_hitPoints == 0) {
        std::cout << "ClapTrap " << this->_name << " is already dead, can't take any damage!" << std::endl;
        return;
    }

    if (amount > this->_hitPoints) {
        this->_hitPoints = 0;
        std::cout << "ClapTrap " << this->_name << " takes " << amount << " points of damage and dies!" << std::endl;
    } else {
        this->_hitPoints -= amount;
        std::cout << "ClapTrap " << this->_name << " takes " << amount << " points of damage! And have now: " << this->_hitPoints << " hit points left." << std::endl;
    }
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (this->_energyPoints == 0) {
        std::cout << "ClapTrap " << this->_name << " is out of energy and can't be repaired!" << std::endl;
        return;
    }
    if (this->_hitPoints == 0) {
        std::cout << "ClapTrap " << this->_name << " is dead, can't be repaired!" << std::endl;
        return;
    }
    
    this->_energyPoints -= 1;
    this->_hitPoints += amount;
    std::cout << "ClapTrap " << this->_name << " is repaired and gains " << amount << " hit points! He's now at: " << this->_hitPoints << " hit points!" << std::endl;
}

std::string	ClapTrap::getName() const
{
	return this->_name;
}