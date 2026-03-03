/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:46:02 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/13 14:14:33 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "usage: ./btc + filename.txt" << std::endl;
		return 1;
	}
	try
	{
		BitcoinExchange exchange(argv[1]);
		exchange.openFile();
		exchange.parseFile();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error:" << e.what() << std::endl;
		return 1;
	}
	return 0;
}	