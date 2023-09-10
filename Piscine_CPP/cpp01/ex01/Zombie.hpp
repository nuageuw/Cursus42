/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:54:27 by aburnott          #+#    #+#             */
/*   Updated: 2023/06/20 12:09:35 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie {
	
public:
	Zombie();
	Zombie(std::string name);
	~Zombie();

	void announce() const;
	void setName(std::string name);
private:
	std::string _name;

};

#endif