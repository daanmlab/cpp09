/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:52:30 by dabalm            #+#    #+#             */
/*   Updated: 2024/04/11 20:42:20 by dabalm           ###   ########.fr       */
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

static std::pair<std::string, std::string> split(std::string str, char delimiter)
{
    std::pair<std::string, std::string> result;
    
    size_t pos = str.find(delimiter);

    result.first = str.substr(0, pos);
    result.second = str.substr(pos + 1);
    
    return result;
}

time_t convertStringToTime(std::string date)
{
    struct tm tm;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_isdst = -1;
    
    strptime(date.c_str(), "%Y-%m-%d", &tm);
    time_t t = mktime(&tm);
    return t;
}

void BitcoinExchange::addData(std::string csvFile)
{
    std::ifstream file(csvFile.c_str());
    if (!file.is_open())
        throw InvalidFileException();
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::pair<std::string, std::string> data = split(line, ',');
        _rates[convertStringToTime(data.first)] = std::atof(data.second.c_str());
    }
    file.close();
}

std::map<time_t, float>::iterator findByDate(std::map<time_t, float> rates, time_t date)
{
    std::map<time_t, float>::iterator it = rates.find(date);
    if (it == rates.end())
    {
        for (it = rates.begin(); it != rates.end(); it++)
        {
            if (it->first > date)
            {
                it--;
                break;
            }
        }
    }
    return it;
}

void BitcoinExchange::printConversionToEuro(std::string from, float amount)
{
    std::map<time_t, float>::iterator it = findByDate(_rates, convertStringToTime(from));
    std::cout << (float)amount << " BTC on " << gmtime(&it->first)->tm_year + 1900 << "-" << gmtime(&it->first)->tm_mon + 1 << "-" << gmtime(&it->first)->tm_mday << " is worth " << (float)(amount * it->second) << " EUR" << std::endl;
}

const char *BitcoinExchange::InvalidFileException::what() const throw()
{
    return "Invalid file";
}