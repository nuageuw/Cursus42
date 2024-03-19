/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:06:36 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 22:06:53 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_H
#define RPN_H

#include <string>

class RPNCalculator {
public:
    RPNCalculator(); 
    RPNCalculator(const RPNCalculator& other); 
    ~RPNCalculator(); 
    RPNCalculator& operator=(const RPNCalculator& other);

    static int evaluate(const std::string& expression);
};

#endif