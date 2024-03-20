/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConversion.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:08:30 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/20 18:04:46 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERSION_HPP
# define SCALARCONVERSION_HPP

# include <string>

class ScalarConversion
{
	private:
		static void	_toChar(std::string str);
		static void	_toInt(std::string str);
		static void	_toFloat(std::string str);
		static void	_toDouble(std::string str);

		ScalarConversion();
		ScalarConversion(const ScalarConversion &copy);
		~ScalarConversion();
		ScalarConversion	&operator=(const ScalarConversion &copy);

	public:
		static void	convert(std::string str);
};

#endif