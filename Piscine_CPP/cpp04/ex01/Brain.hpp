/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:45:40 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/16 16:58:58 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>

class Brain {
private:
    std::string _ideas[100];

public:
    Brain();
    Brain(const Brain &other);
    ~Brain();
    Brain &operator=(const Brain &other);

    void setIdea(const std::string &idea);
    const std::string &getIdea(int index) const;
};

#endif
