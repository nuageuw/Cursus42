/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:26:06 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 17:28:26 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp" // Ajout de l'en-tête pour la classe DiamondTrap

int main() {
    ClapTrap clapTrap("Clap");
    ClapTrap clapTrap2(clapTrap);
    ClapTrap clapTrap3("ClapClone");
    clapTrap3 = clapTrap;

    clapTrap.attack("Enemy");

    ScavTrap scavTrap("Scav");
    ScavTrap scavTrap2(scavTrap);
    ScavTrap scavTrap3("ScavClone");
    scavTrap3 = scavTrap;

    scavTrap.attack("Enemy");
    scavTrap.guardGate();

    FragTrap fragTrap1("F1");
    FragTrap fragTrap2(fragTrap1);

    fragTrap1.attack("target");
    fragTrap1.highFivesGuys();
    fragTrap2.attack("target");
    fragTrap2.highFivesGuys();

    // Tests pour DiamondTrap
    DiamondTrap diamondTrap1("D1");
    DiamondTrap diamondTrap2(diamondTrap1);

    diamondTrap1.FragTrap::attack("target");
    diamondTrap1.highFivesGuys();

    diamondTrap1.ScavTrap::attack("target");
    diamondTrap1.guardGate();

    return 0;
}
