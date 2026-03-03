/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:46:07 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/14 15:27:39 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string& filename):_filename(filename)
{
	std::ifstream file("data.csv");
	if (!file.is_open())
		throw std::runtime_error("error: could not open data.csv");
	std::string line;
	while (std::getline(file, line))
	{
		std::string	date;
		float		value;
		std::istringstream ss(line);
		if (std::getline(ss, date, ',') && ss >> value)
		{
			if (ss.peek() == '\n')
				ss.ignore();
			_data[date] = value;
		}
		else
			continue;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other): _data(other._data), _filename(other._filename) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		_data = other._data;
		_filename = other._filename;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
	if (_file.is_open())
		_file.close();
}

void	BitcoinExchange::printData() const
{
	std::map<std::string, float>::const_iterator it;
	for (it = _data.begin(); it != _data.end(); ++it)
		std::cout << it->first << ": " << it->second << std::endl;
}

void BitcoinExchange::openFile()
{
	_file.open(_filename.c_str());
	if (!_file.is_open())
		throw std::runtime_error("error: could not open input file");
} 

static bool isValidDate(const std::string& date)
{
	if (date.size() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	int year, month, day;
	char dash1, dash2;
	std::istringstream ss(date);
	if (!(ss >> year >> dash1 >> month >> dash2 >> day))
		return false;
	if (dash1 != '-' || dash2 != '-')
		return false;
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;
	if (year < 2009 || year > 2025)
		return false;
	return true;
}

void BitcoinExchange::parseFile()
{
	std::string line;
	std::getline(_file, line);
	while (std::getline(_file, line))
	{
		std::istringstream ss(line);
		std::string date;
		float value;
		if (!std::getline(ss, date, '|') || !(ss >> value))
		{
			std::cerr << "error: bad input => " << line << std::endl;
			continue;
		}
		if (!date.empty() && date[date.size() - 1] == ' ')
			date.erase(date.size() - 1);
		if (!isValidDate(date))
		{
			std::cerr << "error: bad input => " << date << std::endl;
			continue;
		}
		if (value < 0)
		{
			std::cerr << "error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "error: too large a number." << std::endl;
			continue;
		}
		std::map<std::string, float>::iterator it = _data.lower_bound(date);

		if (it == _data.end() || it->first != date)
		{
			if (it == _data.begin())
			{
				std::cerr << "error: bad input => " << date << std::endl;
				continue;
			}
			--it;
		}
		std::cout
			<< date
			<< " => "
			<< value
			<< " = "
			<< value * it->second
			<< std::endl;
	}
}