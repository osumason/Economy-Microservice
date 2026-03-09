// econ.cpp
// Created by Mason Antram on 2/23/2026.
// Reads an integer from wallet.txt and completes a math operation using that number, an int quantity, and a char
// math operator. Writes the resulting number to wallet.txt.

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <unistd.h>
#include <cstdlib>

std::string get_storage_path(std::string filename) {//establishes the filepath to the user's documents folder

    const char *drive = std::getenv("HOMEDRIVE");
    const char *path = std::getenv("HOMEPATH");
    if (!drive || !path) return filename; // Fallback to local if env fails
    return std::string(drive) + std::string(path) + "\\Documents\\" + filename;
}

void initialize () {//creates two text files in the user's documents folder

    std::ofstream wallet(get_storage_path("wallet.txt"));
    wallet << 0;
    wallet.close();

    std::ofstream command(get_storage_path("command.txt"));
    command << "running";
    command.close();
}

void economy (int quantity, char operation) {

    int total = 0;

    try {
        std::ifstream wallet(get_storage_path("wallet.txt"));; //read wall.txt file for integer

        if (!wallet.is_open()) //throw error if wallet.txt can't be found or opened
        {
            throw std::runtime_error("Could not find or open wallet.txt.");
        }

        wallet >> total; //stores int from wallet.txt to a variable
        wallet.close();
    }
    catch (std::exception &what) {
        std::cout << "Exception caught: " << what.what() << '\n';
    }
    catch (...) {
        std::cout << "An unknown error occurred while opening and reading wallet.txt." << '\n';
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


            std::ofstream output(get_storage_path("wallet.txt"));
            output << total; //writes new number to wallet.txt
            output.close();

            std::ofstream output2(get_storage_path("command.txt"));;
            output2 << "running";
            output2.close();

    }
}


void read () {
    std::string check;

    try {
        std::ifstream command(get_storage_path("command.txt")); //read command.txt file

        if (!command.is_open()) //throw error if wallet.txt can't be found or opened
        {
            throw std::runtime_error("Could not find or open command.txt.");
        }
        if (!(command >> check))// throw error if file is empty
        {
            throw std::runtime_error("Could not read command.txt.");
        }

        command.close();

        if (check == "read")//takes the balance from wallet.txt and drops it in command.txt for the user to read
        {
            int num;
            std::ifstream wallet(get_storage_path("wallet.txt"));
            wallet >> num;
            wallet.close();

            std::ofstream output(get_storage_path("command.txt"));
            output << num;
            output.close();

        }
        else if (check != "running")
        { //parses integer from operator and runs the economy function
            int quantity;
            char operation;
            size_t processed_char_count;
            quantity = std::stoi(check, &processed_char_count);
            operation = check[processed_char_count];

            if (operation == '+' || operation == '-' || operation == '*' ||
                 operation == '/') {
                economy(quantity, operation);
            }
        }
    }
    catch (std::exception &what) {
        std::cout << "Exception caught: " << what.what() << '\n';
    }
    catch (...) {
        std::cout << "Unknown exception caught while opening and reading command.txt." << '\n';
    }
}


int main() {

    initialize();

    while (true) {
        read();
        sleep(1);
    }

    return 0;
}
