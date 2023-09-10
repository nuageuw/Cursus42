/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:58:06 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 17:07:50 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

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

    return 0;
}
