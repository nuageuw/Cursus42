/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:58:06 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/15 22:23:52 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
    ClapTrap clapTrap("Domingo");
    ClapTrap clapTrap2(clapTrap);
    ClapTrap clapTrap3("LuiLa");

    clapTrap.attack(clapTrap3.getName());
    clapTrap.takeDamage(5);

    ScavTrap scavTrap("Jiraya");
    ScavTrap scavTrap2(scavTrap);
    ScavTrap scavTrap3("PlusOuMoins");
    scavTrap3 = scavTrap;

    scavTrap.attack(scavTrap3.getName());
    scavTrap3.takeDamage(5);
    scavTrap.guardGate();

    return 0;
}
