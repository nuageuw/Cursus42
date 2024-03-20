/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:53:49 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/20 18:34:40 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <algorithm>

class ValueNotFoundException : public std::exception
{
    public:
        virtual const char* what() const throw() {
            return "Value not found in container";
        };
};

template <typename T>
typename T::iterator easyFind(T& container, int value) {
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it != container.end()) {
        return it;
    }
    throw ValueNotFoundException();
}

#endif