/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:26:06 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/15 23:20:21 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"
int main() {
    //  USELESS BUT IF YOU WANT TO TEST
    
    // ClapTrap clapTrap("Locklear");
    // ClapTrap clapTrap2(clapTrap);
    // ClapTrap clapTrap3("Laink");

    // clapTrap.attack(clapTrap3.getName());
    // clapTrap.takeDamage(5);

    // ScavTrap scavTrap("Terracid");
    // ScavTrap scavTrap2(scavTrap);
    // ScavTrap scavTrap3("CaFaitBeaucoup");

    // scavTrap.attack(scavTrap3.getName());
    // scavTrap3.takeDamage(5);
    // scavTrap.guardGate();

	// FragTrap fragTrap1("Laupok");
    // FragTrap fragTrap2(fragTrap1);
    // FragTrap fragTrap3("Amixem");

    // fragTrap1.attack(fragTrap3.getName());
    // fragTrap1.highFivesGuys();
    // fragTrap2.attack(fragTrap3.getName());
    // fragTrap2.highFivesGuys();

    DiamondTrap diamondTrap1("Etienne");
    DiamondTrap diamondTrap2(diamondTrap1);
    DiamondTrap diamondTrap3("Yvan");

    diamondTrap1.attack(diamondTrap3.getName());
    diamondTrap1.beRepaired(34);
    diamondTrap1.whoAmI();

    diamondTrap2.attack(diamondTrap3.getName());
    diamondTrap2.takeDamage(5);
    diamondTrap2.whoAmI();

    diamondTrap3.whoAmI();
    diamondTrap3.highFivesGuys();
    diamondTrap3.guardGate();

    return 0;
}
