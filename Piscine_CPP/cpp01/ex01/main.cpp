/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:53:51 by aburnott          #+#    #+#             */
/*   Updated: 2023/08/28 14:13:42 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie *zombieHorde(int N, std::string name);

int main(void) {
    int N = 5;
	Zombie *horde = zombieHorde(N, "Mireille");
	for (int i = 0; i < N; i++) {
		horde[i].announce();
	}
	delete[] horde;
	return 0;
}