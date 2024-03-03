/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reshivii <reshivii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:45:29 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/02 20:24:35 by reshivii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie	*newZombie(std::string name);
void	randomChump(std::string name);

int main(void) {
	Zombie *z1 = newZombie("Gotaga");
	z1->announce();
	randomChump("Squeezie");
	delete z1;
	return 0;
}