/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:52:46 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 16:52:47 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main() {
    ClapTrap clap1("Clappy");
    ClapTrap clap2 = clap1;

    clap1.attack("Enemy");
    clap2.takeDamage(5);
    clap2.beRepaired(3);

    return 0;
}
