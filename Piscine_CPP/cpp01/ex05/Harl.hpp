/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 00:43:56 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/27 13:06:35 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HARL_HPP
# define HARL_HPP

# include <iostream>
# include <string>


#include <string>

class Harl {

public:
    Harl();
    ~Harl();
    void complain(std::string level);
private:
    void _debug();
    void _info();
    void _warning();
    void _error();

};

#endif