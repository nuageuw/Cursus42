/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:25:00 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 00:15:28 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
#define DATA_HPP

class Data {
public:
	Data();
	Data(int value);
	~Data();
	Data(Data const &other);

	Data &operator=(const Data assign);
	
    int getValue() const;

private:
    int m_value;
};

#endif
