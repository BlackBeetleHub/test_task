//
// Created by beetle on 6/10/18.
//
#include <string>
#include <iostream>
#include <limits>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>
#include <gmpxx.h>

typedef mpz_class BigInt;

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

BigInt prodTree(const BigInt &l, const BigInt &r) {
    if (l > r)
        return 1;
    if (l == r)
        return l;
    if (r - l == 1)
        return l * r;
    BigInt m = (l + r) / 2;
    return prodTree(l, m) * prodTree(m + 1, r);
}

BigInt fact(const BigInt & n)
{
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;
    if (n == 1 || n == 2)
        return n;
    return prodTree(2, n);
}

bool isNumber(std::string const &strNumber) {
    try {
        std::stoi(strNumber);
    } catch (std::invalid_argument &invalid_argument) {
        std::cout << "[error] Input number not correct (not a number). (" << invalid_argument.what() << ")"
                  << std::endl;
        return false;
    } catch (std::out_of_range &out_of_range) {
        std::cout << "[error] Input number too much. Max available number is " << std::numeric_limits<int>::max() <<
                  std::endl;
        return false;
    }
    return true;
}

BigInt getCombinations(const BigInt &n, const BigInt &k) {
    return (fact(n) / fact(k)) / fact(n - k);
}

int main() {
    std::string command;
    std::cout << "[info] Example usage: \n>>>6 3\n<<<20" << std::endl;
    std::cout << "[info] Enter \"exit\" for stop program." << std::endl;
    while (true) {
        std::cout << "Enter n and k / or exit: ";
        std::getline(std::cin, command);
        if (command == "exit") {
            std::cout << "Goodbye..." << std::endl;
            return 0;
        }
        std::vector<std::string> numbers = split(command, ' ');
        if (numbers.size() < 2) {
            std::cout << "[error] Count numbers must be equal 2." << std::endl;
            continue;
        }
        if (numbers.size() > 2) {
            std::cout << "[warn] Unused numbers." << std::endl;
        }
        int n = std::stoi(numbers[0]);
        int k = std::stoi(numbers[1]);
        if (k > n) {
            std::cout << "[error] k can not be greater than n" << std::endl;
            continue;
        }
        std::cout << "Answer: " << getCombinations(std::stoi(numbers[0]), std::stoi(numbers[1])) << std::endl;
    }
    return 0;
}