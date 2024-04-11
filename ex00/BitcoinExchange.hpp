/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BItcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:43:04 by dabalm            #+#    #+#             */
/*   Updated: 2024/04/11 03:13:29 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

class BitcoinExchange
{
private:
    std::map<std::string, double> _rates;
    std::map<std::string, double> _volumes;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &copy);
    BitcoinExchange &operator=(const BitcoinExchange &copy);
    ~BitcoinExchange();

    void addData(std::string csvFile);

    void printConversionToEuro(std::string from, double amount);

    class InvalidFileException : public std::exception
    {
        virtual const char *what() const throw();
    };
};
