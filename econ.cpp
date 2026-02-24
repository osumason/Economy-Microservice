// econ.cpp
// Created by Mason Antram on 2/23/2026.
// Reads an integer from wallet.txt and completes a math operation using that number, an int quantity, and a char
// math operator. Writes the resulting number to wallet.txt.

#include "econ.hpp"

#include <iostream>
#include <fstream>
#include <typeinfo>

void initialize (int num)
{
    try
    {
    std::ofstream wallet("wallet.txt");

    if (!wallet.is_open()) //throw error if wallet.txt can't be found or opened
    {
        throw std::runtime_error("Could not find or open wallet.txt.");
    }

    if (typeid(num) != typeid(int)) //throw error if quantity is not an integer
    {
        throw std::runtime_error("Variable passed in is not an integer.");
    }

    wallet << num;
    wallet.close();

    }
    catch (std::exception& what)
    {
        std::cout << "Exception caught: " << what.what() << '\n';
    }
    catch (...)
    {
        std::cout << "An unknown error occurred while opening and writing to wallet.txt." << '\n';
    }
}

void economy (int quantity, char operation)
{
    int total = 0;

    try
    {
        std::ifstream wallet("wallet.txt"); //read wall.txt file for integer

        if (!wallet.is_open()) //throw error if wallet.txt can't be found or opened
        {
            throw std::runtime_error("Could not find or open wallet.txt.");
        }

        if (!(wallet >> total)) //throw error if wallet.txt is empty or has non-integer data
        {
            throw std::runtime_error("wallet.txt is either empty or contains non-integer data.");
        }

        wallet >> total; //stores int from wallet.txt to a variable

        wallet.close();
    }
    catch (std::exception& what)
    {
        std::cout << "Exception caught: " << what.what() << '\n';
    }
    catch (...)
    {
        std::cout << "An unknown error occurred while opening and reading wallet.txt." << '\n';
    }

    try
    {

        if (operation != '+' && operation != '-' && operation != '*' && operation != '/') //throw error if char isn't a basic math operator
        {
            throw std::runtime_error("Operator passed in was not + - / *");
        }

        if (typeid(quantity) != typeid(int)) //throw error if quantity is not an integer
        {
            throw std::runtime_error("Quantity is not an integer.");
        }

        switch (operation) //completes math operation using variables total, quantity, and operation
        {
            case '+':
                total += quantity;
                break;

            case '-':
                total -= quantity;
                break;

            case '/':
                total /= quantity;
                break;

            case '*':
                total *= quantity;
                break;

            default:
                total = -1;
        }

        std::ofstream output("wallet.txt");

        output << total; //writes new number to wallet.txt

        output.close();

    }
    catch (std::exception& what)
    {
        std::cout << "Exception caught: " << what.what() << '\n';
    }
    catch (...)
    {
        std::cout << "Unknown exception caught while running math operation and writing to wallet.txt." << '\n';
    }
}
