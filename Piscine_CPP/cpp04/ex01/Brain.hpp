/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reshivii <reshivii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:45:40 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/03 14:38:44 by reshivii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>

class Brain {
private:
    std::string _ideas[100];
    unsigned int	_index;

public:
    Brain();
    ~Brain();

    void setIdea(const std::string &idea);
    const std::string &getIdea(int index) const;
};

#endif
