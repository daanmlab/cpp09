/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 03:05:23 by dabalm            #+#    #+#             */
/*   Updated: 2024/04/11 20:47:49 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// example: 2012-01-11 | 2147483648

bool isOverMax(std::string str)
{
    if (str.size() > 10)
        return true;
    if (str.size() == 10 && str > "2147483647")
        return true;
    return false;
}

std::pair<std::string, float>    checkLine(std::string str)
{
    std::pair<std::string, float> pair;
    std::string date;
    std::string value;
    std::string::size_type pos;
    
    pos = str.find(" | ");
    if (pos == std::string::npos)
        throw std::runtime_error("Invalid input: " + str);
    date = str.substr(0, pos);
    value = str.substr(pos + 3);
    if (value[0] == '-')
        throw std::runtime_error("Invalid input: " + str);
    if (isOverMax(value))
        throw std::runtime_error("Invalid input: " + str);
    if (date.empty() || value.empty())
        throw std::runtime_error("Invalid input: " + str);
    pair.first = date;
    pair.second = std::atof(value.c_str());
    
    if (pair.second > std::numeric_limits<float>::max())
        throw std::runtime_error("Invalid input: " + str);
    return pair;
}

int main(int argc, char **argv)
{
    BitcoinExchange exchange;
    std::ifstream file;
    std::pair<std::string, float> temp;
    
    if (argc != 2)
    {
        std::cerr << "Usage: ./btc [input file]" << std::endl;
        return 1;
    }

    try
    {
        // set database
        exchange.addData("./data.csv");
        // open input file
        file.open(argv[1]);
        if (!file.is_open())
            throw std::runtime_error("Could not open file");
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
        // read input file
    while (!file.eof())
    {
        std::string line;
        std::getline(file, line);
        if (line.empty() || line == "date | value")
            continue;
        try
        {
            temp = checkLine(line);
            exchange.printConversionToEuro(temp.first, temp.second);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
        
    return 0;
}