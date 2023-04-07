#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include <time.h>
#include <regex>
#include <map>
#include <numeric>
#include "Input.h"
#include <limits>
#include <stdio.h>
#include <ctime>
#include <cctype>





class Checkout_sys
{
private:
	long long active_credit_card = 0;
	long long creditCardNumber = 0;
	int sum = 0;
	int count = 0;
	unsigned long long divisor = 10;
	char types[20];


public:
    
void system_check()
{

	std::cout << "\n"
		<<"\t"<< "Welcome to ASD Supermarket Checkout Point -->" << std::endl;
	    std::cout<<"\n"<<"\t"<<"Enter Your details below to Pay"<< std::endl;
}

void get_customer_name()
{
	bool valid_input;
		do
		{
			std::string shoppers_name;      // Stores shoppers name 
			std::cout <<"\n"<<"\t"<< "Please Enter your first name and last name: ";
			std::getline(std::cin, shoppers_name);
			std::cout << "\n" << "\t" << "Customer name: " << shoppers_name << std::endl;
			

			valid_input = true;
		
			// std::cout <<"\n"<<"\t"<< "Customer name: " << shoppers_name << std::endl;
			
			for (std::size_t i{}; i < shoppers_name.length() && valid_input; ++i)
			{
				if (!(std::isalpha(static_cast<unsigned char>(shoppers_name[i])) ||
					std::isspace(static_cast<unsigned char>(shoppers_name[i]))))
					
				{
					valid_input = false;
					std::cout <<"\n"<<"\t"<<"Invalid! Type in your first name followed by space and last name only!" << "\n";
					std::cout << "\n" << "\t" << "Press Enter to continue.......";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					
					
					//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					
					
					break;
				}
				return;
			}
			
			
		} while (!valid_input);
		
}

void get_customer_address()
{
	bool get_valid_input;
	do
	{
		std::string shoppers_address;  // Stores shoppers address
		std::cout << "\n" << "\t" << "Enter your address: ";
		std::getline(std::cin, shoppers_address);
		std::cout << "\n" << "\t" << "Customer address: " << shoppers_address << std::endl;

		get_valid_input = true;

		for (std::size_t i{}; i < shoppers_address.length() && get_valid_input; ++i)
		{
			if (!(std::isalpha(static_cast<unsigned char>(shoppers_address[i])) ||
				std::isspace(static_cast<unsigned char>(shoppers_address[i])) ||
				std::isdigit(static_cast<unsigned int>(shoppers_address[i]))))

			{
				get_valid_input = false;
				std::cerr << "\n" << "\t" << "Invalid input! Type in your address without Symbols,commas or dots." << "\n";
				std::cout << "\n" << "\t" << "Press Enter to continue.......";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
			}
			
		}


	} while (!get_valid_input);

	
}


bool isValidPostcode(std::string postcode) // Bool function to validate if Post Code is valid or not
{
	do
	{
		std::regex pattern("^[A-Z]{1,2}[0-9]{1,2}[A-Z]?(\\s*[0-9][A-Z]{1,2})?$");
		std::string post_code;        // stores shoppers post code
		std::cout << "\n" << "\t" << "Enter your post code: ";
		std::getline(std::cin, postcode);

		bool match = std::regex_match(postcode, pattern);

		if (!match)
		{
			std::cerr << "\n" << "\t" << "Invalid PostCode! Correct Format example(SW15 4JD). Try again";
			std::cout << "\n" << "\t" << "Press Enter to continue.......";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
		}
		else
		{
			std::cout << "\n" << "\t"<<"Post Code: " << postcode << std::endl;
			return std::regex_match(postcode, pattern);
			break;
		}
			
	} while (true);
	
	
} 

double prompt_for_payment () // Function gets customers creditcard number and validates it. 
{
	{

		std::cout << "\n" << "\t"<< "Enter your credit card Number: ";
		std::cin >> creditCardNumber;
		
		
		while (std::cin.fail() || std::to_string(creditCardNumber).length() < 10 ||
			   std::to_string(creditCardNumber).length() > 19)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\n" << "\t" << "Invalid Input! Please use a numeric value and a minimum of 10 digits..." << std::endl;
			std::cout << "\n" << "\t" << "Enter your credit card Number: ";
			std::cin >> creditCardNumber;
		}
		std::cout << "\n" << "\t"<< "Credit Card number: " << creditCardNumber << std::endl;


		// Condition 1
		active_credit_card = creditCardNumber;
		while (active_credit_card > 0)
		{
			int last_digit = active_credit_card % 10;
			sum = sum + last_digit;
			active_credit_card = active_credit_card / 100;
		}
		// Condition 2
		active_credit_card = creditCardNumber / 10;
		while (active_credit_card > 0)
		{
			int last_sec_digit = active_credit_card % 10;
			int mul_two = last_sec_digit * 2;
			sum = sum + (mul_two % 10) + (mul_two / 10);
			active_credit_card = active_credit_card / 100;
		}

		// Check card length
		active_credit_card = creditCardNumber;
		while (active_credit_card != 0)
		{
			active_credit_card = active_credit_card / 10;
			count++;
		}

		for (int i = 0; i < count - 2; i++)
		{
			divisor = divisor * 10;
		}

		unsigned long long first_digit = creditCardNumber / divisor;
		unsigned long long first_two_digit = creditCardNumber / (divisor / 10);

		if (sum % 10 == 0)
		{
			if (first_digit == 4 && (count == 13 || count == 16))
			{
				std::cout << "\n" << "\t" << "Valid \n";
				std::cout << "\n" << "\t" << "Credit Card Type: ";
				strcpy_s(types, "VISA");
			}
			else if ((first_two_digit == 34 || first_two_digit == 37) && count == 15)
			{
				std::cout << "\n" << "\t" << "Valid \n";
				std::cout << "\n" << "\t" << "Credit Card Type: ";
				strcpy_s(types, "AMERICAN EXPRESS");
			}
			else if ((50 < first_two_digit && first_two_digit < 56) && count == 16)
			{
				std::cout << "\n" << "\t" << "Valid \n";
				std::cout << "\n" << "\t" << "Credit Card Type: ";
				strcpy_s(types, "MASTER CARD");
			}
			else if ((first_two_digit == 60 || first_two_digit == 64) && count == 16)
			{
				std::cout << "\n" << "\t" << "Valid \n";
				std::cout << "\n" << "\t" << "Credit Card Type: ";
				strcpy_s(types, "DISCOVERY CARD");
			}

			else
			{
				std::cout << "\n" << "\t" << "Valid \n";
				strcpy_s(types, "\n"  "\t" "Unamed Card Type");
			}
		}
		else
		{
			strcpy_s(types, "\n"  "\t" "Invalid Card");
		}

		std::cout << types;
		return creditCardNumber;
	}

	std::cout << std::endl;

}

bool isValid_card_expiry_date(std::string card_Expiry_date) 
{
	do
	{
		std::regex patternn("^([0]?[1-9]|[1|2][0-9]|[3][0|1])[./-]([0]?[1-9]|[1][0-2])[./-]([0-9]{4}|[0-9]{2})$");
		
		//("^(((0[1-9]|[12][0-9]|30)[-/]?(0[13-9]|1[012])|31[-/]?(0[13578]|1[02])|(0[1-9]|1[0-9]|2[0-8])[-/]?02)[-/]?[0-9]{4}|29[-/]?02[-/]?([0-9]{2}(([2468][048]|[02468][48])|[13579][26])|([13579][26]|[02468][048]|0[0-9]|1[0-6])00))$");
		std::string card_Expiry_date;
		std::cout << "\n" << "\t" << "Enter Credit Card Expiry Date in DD/MM/YYYY format: ";
		std::cin >> card_Expiry_date;
		//std::getline(std::cin, card_Expiry_date);
		
		bool link = std::regex_match(card_Expiry_date, patternn);
	
		if (!link)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "\n" << "\t" << "Invalid Date format! Enter a valid date in dd/mm/yyyy format: ";
			//std::cout << "\n" << "\t" << "Press Enter to continue.......";
			
			
		}
		
		else
		{
			std::cout << "\n" << "\t" << "Credit Card Expiry Date: " << card_Expiry_date << std::endl;
			return std::regex_match(card_Expiry_date, patternn);
		
		}
	
	} while(true);
}

bool  isValidcardSecret_code(std::string card_secret_code)
{
	do
	{
		std::regex pattern_n("^[0-9]{3,4}$");
		std::cout << "\n" << "\t" << "Enter Credit Card Secret Code: ";
		std::cin >> card_secret_code;
		//std::getline(std::cin, card_secret_code);

		bool sync = std::regex_match(card_secret_code, pattern_n);

		if (!sync)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\n" << "\t" << "Invalid Entry!";
			std::cout << "\n" << "\t" <<"Enter numbers not less than three and not more than four :" ;
			
			
			
		}
		else
		{
			std::cout << "\n" << "\t" << "Credit Card Secret Code: " << card_secret_code << std::endl;
			return std::regex_match(card_secret_code, pattern_n);
			
		}
		

	} while (true);
	
}

void list_of_items() // Function displays Item and price
{

	std::cout << "\n" << "\t "<< "===The Unit Price for Items===" << std::endl;
	std::cout << "\n" << "\t "<< "  "<< "Baked Beans: 1.20" << std::endl;
	std::cout << "\n" << "\t "<< "  "<< "Popcorn: 0.80" << std::endl;
	std::cout << "\n" << "\t "<< "  "<< "Evaporated Milk: 1.15" << std::endl;
	std::cout << "\n" << "\t "<< "  "<< "Bread: 2.20" << std::endl;
}

 double Calculate_item_quantity() // Function calculates Items selected.
{

	const double baked_beans = 1.20, popcorn = 0.80,
		evaporated_milk = 1.15, bread = 2.34;
	int bakedbeans, pop_corn, evaporatedmilk, b_read;

	do
	{
		std::cout << "\n" << "\t" << "Enter the quantity of Baked Beans purchased: ";
		std::cin >> bakedbeans;
		std::cout << "\n" << "\t" << "Enter the quantity of Popcorn purchased: ";
		std::cin >> pop_corn;
		std::cout << "\n" << "\t" << "Enter the quantity of Evaporated Milk purchased: ";
		std::cin >> evaporatedmilk;
		std::cout << "\n" << "\t" << "Enter the quantity of Bread purchased: ";
		std::cin >> b_read;
		
		std::cout << "\n" << "\t" << "====Total Item Purchased=======" << std::endl;
		std::cout << "\n" << "\t" << bakedbeans << "x" << " Baked Beans.";
		std::cout << "\n" << "\t" << pop_corn << "x" << " Popcorn.";
		std::cout << "\n" << "\t" << evaporatedmilk << "x" << " Evaporated milk.";
		std::cout << "\n" << "\t" << b_read << "x" << " Bread.";

		int subtotal(bakedbeans + pop_corn + evaporatedmilk + b_read);
		std::cout << "\n" << "\t" << "Total Quantity of Item purchased :" << subtotal << " Items" << std::endl;

		const double vat{ 0.20 };
		const double salesTax(subtotal * vat);

		std::cout << "\n" << "\t" << "Sales VAT: " << salesTax << std::endl;

		std::cout << "\n" << "\t" << "Total cost: " << ((baked_beans * bakedbeans) + (popcorn * pop_corn) + (evaporated_milk * evaporatedmilk) + (bread * b_read) + salesTax) << std::endl;
		
		if (!(std::cin >> bakedbeans >> pop_corn >> evaporatedmilk >> b_read))
		{
			std::cout << "\n" << "\t" << "Invalid! Please Use only Numeric Value! ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (!(std::cin));

     return 0;
}
};


int main(int arg, char** argv)
{
	Checkout_sys sys;
	sys.system_check();
	sys.get_customer_name();
	sys.get_customer_address();
	std::string post_code = "SW15 4JD";
	sys.isValidPostcode(post_code);
	sys.prompt_for_payment();
	std::string card_ex_date = "11/12/2023";
	sys.isValid_card_expiry_date(card_ex_date);
	std::string card_sec_code = "234";
	sys.isValidcardSecret_code(card_sec_code);
	sys.list_of_items();
    sys.Calculate_item_quantity();

	return 0;
	
}