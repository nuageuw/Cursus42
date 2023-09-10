/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:45:40 by aburnott          #+#    #+#             */
/*   Updated: 2023/07/29 17:45:46 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>

class Brain {
private:
    std::string ideas[100];

public:
    Brain();
    ~Brain();

    void setIdea(int index, const std::string &idea);
    const std::string &getIdea(int index) const;
};

#endif
