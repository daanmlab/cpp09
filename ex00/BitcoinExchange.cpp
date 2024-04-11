/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:52:30 by dabalm            #+#    #+#             */
/*   Updated: 2024/04/11 03:19:45 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
    *this = copy;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
    if (this != &copy)
    {
        this->_rates = copy._rates;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

std::vector<std::string> split(std::string str, char delimiter)
{
    std::vector<std::string> result;
    std::string token;
    size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + 1);
    }
    result.push_back(str);
    return result;
}

void BitcoinExchange::addData(std::string csvFile)
{
    std::ifstream file(csvFile);
    if (!file.is_open())
        throw InvalidFileException();
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::vector<std::string> data = split(line, ',');
        if (data.size() != 2)
            throw InvalidFileException();
        std::cout << data[0] << " " << data[1] << std::endl;
        _rates[data[0]] = std::stod(data[1]);
    }
    file.close();
}

void BitcoinExchange::printConversionToEuro(std::string from, double amount)
{
    if (_rates.find(from) == _rates.end())
    {
        // Find the closest date
        std::string closestDate;
        double closestRate = 0.0;
        double minDifference = std::numeric_limits<double>::max();
        std::string closestRateDate; // Updated variable name

        for (std::map<std::string, double>::const_iterator it = _rates.begin(); it != _rates.end(); ++it)
        {
            double difference = std::abs(std::stod(it->first) - std::stod(from));
            if (difference < minDifference)
            {
                minDifference = difference;
                closestRateDate = it->first; // Updated variable assignment
                closestRate = it->second;
            }
        }

        std::cout << "Closest date: " << closestRateDate << std::endl; // Updated variable name
        std::cout << amount << " BTC on " << from << " = " << amount * closestRate << " EUR" << std::endl;
    }
    else
    {
        std::cout << amount << " BTC on " << from << " = " << amount * _rates[from] << " EUR" << std::endl;
    }
    if (_rates.find(from) == _rates.end())
        std::cout << "Currency not found" << std::endl;
    else
        std::cout << amount << " BTC"
                  << " on " << from << " = " << amount * _rates[from] << " EUR" << std::endl;
}

const char *BitcoinExchange::InvalidFileException::what() const throw()
{
    return "Invalid file";
}