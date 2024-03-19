/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:18:54 by aburnott          #+#    #+#             */
/*   Updated: 2024/03/18 21:49:22 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTC_HPP
# define BTC_HPP

# define WHITESPACES " \n\r\t\f\v"

# include <map>
# include <string>

class BitcoinExchange
{
	private:
		std::map<std::string, float>	_map;

		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange	&operator=(const BitcoinExchange &other);

		std::string _parse_date(const std::string& str, size_t pos);
		float _parse_number(const std::string& str, size_t pos);
		bool _valid_date(const std::string &date);
		bool _valid_number(const std::string &number);
		void _find_rate(const std::string& date, float value);

	public:
		BitcoinExchange();
		~BitcoinExchange();
		void	process_input(const std::string &filename);
};

#endif