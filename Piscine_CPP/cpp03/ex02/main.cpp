/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:58:06 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/15 23:21:14 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
    ClapTrap clapTrap("Avamind");
    ClapTrap clapTrap2(clapTrap);
    ClapTrap clapTrap3("BagheraJones");

    clapTrap.attack(clapTrap3.getName());
    clapTrap.takeDamage(5);

    ScavTrap scavTrap("Zerator");
    ScavTrap scavTrap2(scavTrap);
    ScavTrap scavTrap3("Horty");

    scavTrap.attack(scavTrap3.getName());
    scavTrap3.takeDamage(5);
    scavTrap.guardGate();

	FragTrap fragTrap1("AntoineDaniel");
    FragTrap fragTrap2(fragTrap1);
    FragTrap fragTrap3("JaiPlusDeNom");

    fragTrap1.attack(fragTrap3.getName());
    fragTrap1.highFivesGuys();
    fragTrap1.beRepaired(7);
    fragTrap2.attack(fragTrap3.getName());
    fragTrap2.highFivesGuys();
    fragTrap2.takeDamage(5);

    return 0;
}
