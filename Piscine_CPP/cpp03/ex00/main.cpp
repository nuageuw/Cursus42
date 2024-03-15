/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:52:46 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/15 20:40:22 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main() {
    ClapTrap clap1("Gotaga");
    ClapTrap clap2("Doigby");

    clap1.attack(clap2.getName());
    clap2.takeDamage(5);
    clap2.beRepaired(3);

    return 0;
}
