#pragma once
#include <iostream>
#include <string>



template<typename T>
void getInput(T& input, const std::string ask_user)
{
	std::cout << ask_user;
	std::cin >> input;

	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid Input! Please Try again\n";

		std::cout << ask_user;
		std::cin >> input;
	}
}