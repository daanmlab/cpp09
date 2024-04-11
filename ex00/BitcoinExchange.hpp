/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:43:04 by dabalm            #+#    #+#             */
/*   Updated: 2024/04/11 20:11:24 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <limits>
#include <exception>
#include <ctime>
#include <iomanip>

class BitcoinExchange
{
private:
    std::map<time_t, float> _rates;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &copy);
    BitcoinExchange &operator=(const BitcoinExchange &copy);
    ~BitcoinExchange();

    void addData(std::string csvFile);

    void printConversionToEuro(std::string from, float amount);

    class InvalidFileException : public std::exception
    {
        virtual const char *what() const throw();
    };
};
