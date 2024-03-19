/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:19:58 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 21:24:16 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btc.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    if (argc != 2)
	{
		std::cerr << "Error: usage: ./btc <filename>\n";
		return 1;
	}
	BitcoinExchange	btc;
	btc.process_input(argv[1]);

    return 0;
}
