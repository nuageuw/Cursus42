/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:58:06 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 17:16:00 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

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

    return 0;
}
