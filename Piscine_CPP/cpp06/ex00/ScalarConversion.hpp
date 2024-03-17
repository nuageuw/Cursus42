/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConversion.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:08:30 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/17 01:05:14 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERSION_HPP
# define SCALARCONVERSION_HPP

# include <iostream>
# include <string>

class ScalarConversion
{
public:
	ScalarConversion();
	~ScalarConversion();
	ScalarConversion(const ScalarConversion& other);
	ScalarConversion& operator=(const ScalarConversion& other);

	static void convert(std::string str);
	
private:
	static void _convertChar(const std::string& str);
	static void _convertDouble(const std::string& str);
	static void _convertFloat(const std::string& str);
	static void _convertInteger(const std::string& str);
	
	// static bool _isChar(const std::string& str);
	static bool _isDouble(const std::string& str);
	static bool _isFloat(const std::string& str);
	static bool _isInteger(const std::string& str);
};

#endif