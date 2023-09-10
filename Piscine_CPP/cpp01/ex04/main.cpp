/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:59:02 by aburnott          #+#    #+#             */
/*   Updated: 2023/08/28 14:23:07 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

void replaceInFile(char **filename, const std::string &s1, const std::string &s2) {
    std::ifstream inputFile(filename[1]);
    if (!inputFile) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename[1] << std::endl;
        return;
    }

    std::ofstream outputFile((std::string(filename[1]) + ".replace").c_str(), std::ios::trunc);
    if (!outputFile) {
        std::cerr << "Erreur : Impossible de créer le fichier " << filename[1] << ".replace" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::string::size_type start = 0;
        while (true) {
            std::string::size_type found = line.find(s1, start);
            if (found == std::string::npos) {
                break;
            }
            outputFile << line.substr(start, found - start) << s2;
            start = found + s1.length();
        }
        outputFile << line.substr(start) << std::endl;
    }

    std::cout << "Remplacement effectué avec succès. Le nouveau fichier est : " << filename[1] << ".replace" << std::endl;
}

int main(int ac, char** av) {
    if (ac != 4) {
        std::cerr << "Usage: " << av[0] << " <filename> <s1> <s2>" << std::endl;
        return 1;
    }

    std::string s1 = av[2];
    std::string s2 = av[3];

    replaceInFile(av, s1, s2);

    return 0;
}