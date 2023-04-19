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
#include <cstring>
#include <iomanip>







class Checkout_sys
{
private:
	long long active_credit_card = 0;
	long long creditCardNumber = 0;
	int sum = 0;
	int count = 0;
	unsigned long long divisor = 10;
	const char* str = "Card Type";
	char types [250];
	std::string shoppers_name;
	std::string shoppers_address;
	std::string postcode;
	std::string card_secret_code;
	std::string card_Expiry_date;
	double baked_beans = 1.20, popcorn = 0.80,
		evaporated_milk = 1.15, bread = 2.34; 
	float vat = 0.2, vat_amount, salesTax = 0, totalCost,finalCost, totalTax = 0;
	int bakedbeans = 0, pop_corn = 0, evaporatedmilk = 0, b_read = 0;
	std::ofstream reciept;
	
	


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
			std::cout <<"\n"<<"\t"<< "Please Enter your first name and last name: ";
			std::getline(std::cin, shoppers_name);
			transform(shoppers_name.begin(), shoppers_name.end(), shoppers_name.begin(), ::toupper);
			std::cout << "\n" << "\t" << "Customer name: " << shoppers_name << std::endl;
			

			valid_input = true;
		

			for (std::size_t i{}; i < shoppers_name.length() && valid_input; ++i)
			{
				if (!(std::isalpha(static_cast<unsigned char>(shoppers_name[i])) ||
					std::isspace(static_cast<unsigned char>(shoppers_name[i]))))
					
				{
					valid_input = false;
					std::cout <<"\n"<<"\t"<<"Error! Name must not include numbers or symbols..." << "\n";
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
		
		std::cout << "\n" << "\t" << "Enter your address: ";
		std::getline(std::cin, shoppers_address);
		transform(shoppers_address.begin(), shoppers_address.end(), shoppers_address.begin(), ::toupper);
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


bool isValidPostcode() // Bool function to validate if Post Code is valid or not
{
	do
	{
		//std::regex pattern("^[A-Z]{1,2}[0-9]{1,2}[A-Z]?(\\s*[0-9][A-Z]{1,2})?$");
		std::regex pattern("^[a-zA-Z]{1,2}[0-9]{1,2}[a-zA-Z]?(\\s*[0-9][a-zA-Z]{1,2})?$");
		std::cout << "\n" << "\t" << "Enter your post code: ";
		std::getline(std::cin, postcode);
		transform(postcode.begin(), postcode.end(), postcode.begin(), ::toupper);
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
		return 0;
	}

	std::cout << std::endl;

}

bool isValid_card_expiry_date() 
{
	do
	{
		std::regex patternn("^([0]?[1-9]|[1|2][0-9]|[3][0|1])[./-]([0]?[1-9]|[1][0-2])[./-]([0-9]{4}|[0-9]{2})$");
		
		//("^(((0[1-9]|[12][0-9]|30)[-/]?(0[13-9]|1[012])|31[-/]?(0[13578]|1[02])|(0[1-9]|1[0-9]|2[0-8])[-/]?02)[-/]?[0-9]{4}|29[-/]?02[-/]?([0-9]{2}(([2468][048]|[02468][48])|[13579][26])|([13579][26]|[02468][048]|0[0-9]|1[0-6])00))$");
		
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

bool  isValidcardSecret_code()
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

	

	bool alphabet = false;

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

	
		if (!(std::cin.fail()))
		{
			if (bakedbeans >= 1 && pop_corn >= 1 && evaporatedmilk >= 1 && b_read >= 1)
			{
				std::cout << "\n" << "\t" << "====Total Item Purchased=======" << std::endl;
					std::cout << "\n" << "\t" << bakedbeans << "x" << " BAKED BEANS.";
					std::cout << "\n" << "\t" << pop_corn << "x" << " POPCORN.";
					std::cout << "\n" << "\t" << evaporatedmilk << "x" << " EVAPORATED MILK.";
					std::cout << "\n" << "\t" << b_read << "x" << " BREAD.";

					totalCost = (bakedbeans + pop_corn + evaporatedmilk + b_read);
					std::cout << "\n" << "\t" << "Total amount :" << totalCost << std::endl;

					vat_amount = totalCost * vat;

					finalCost = ((baked_beans * bakedbeans) + (popcorn * pop_corn) + (evaporated_milk * evaporatedmilk) + (bread * b_read) + vat_amount);
				    std::cout << "\n" << "\t" << "Sales VAT: " << vat_amount << std::endl;
					std::cout << "\n" << "\t" << "Total cost: " << totalCost << std::endl;
				    //std::cout << "\n" << "\t" << "Total cost: " << ((baked_beans * bakedbeans) + (popcorn * pop_corn) + (evaporated_milk * evaporatedmilk) + (bread * b_read) + salesTax) << std::endl;
					std::cout << std::endl;
				alphabet = true;
			}
			else
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "\n" << "\t" << "Enter a number not less than 0 to process purchase......";
			}
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\n" << "\t" << "Invalid! Please Use only Numeric Value! ";
		}
	}while(!(alphabet));
	return 0;
 } 

 void write_to_file()
 {
	 std::ofstream reciept{ "CheckoutSystem.txt", std::ofstream::out};
	 reciept <<"\t"<< std::setiosflags(std::ios::left) << std::setw(15) << "*******SHOP RECIEPT**************" << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::right) <<std::setw(15)  <<"ADS SUPERMARKET" << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::right) <<std::setw(17)  <<"10,Cardlane,London. SW19 4UD " << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left)  <<std::setw(17)  <<"Tel :01483-220494 " << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left)  <<std::setw(14)  <<"RECIEPT: 01654" << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left)  <<std::setw(17)  <<"DATE: 15/05/2023   " << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left)  <<std::setw(17)  <<"CASHIER: JOHN DOE  " << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left)  <<std::setw(15) <<"----------------------------------"  << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left)  <<std::setfill(' ')  <<std::setw(1) << "NAME:" << std::setw(28) << shoppers_name << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left)  <<std::setfill(' ')  <<std::setw(6) << "ADDRESS:" << std::setw(28) << shoppers_address << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left)  <<std::setfill(' ')  <<std::setw(6) << "POSTCODE:" << std::setw(24) << postcode << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left)  <<std::setfill(' ')  <<std::setw(6) << "CREDIT CARD No:" << std::setw(18) << creditCardNumber << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left)  <<std::setfill(' ')  <<std::setw(6) << "Valid  \n";
	 reciept <<"\t"<< std::setiosflags(std::ios::left)  <<std::setfill(' ')  <<std::setw(6) << "Credit Card Type: ";
	 reciept.write(types, strlen(types));
	 reciept <<"\n"<<"\t"<< std::setiosflags(std::ios::left)  <<std::setfill(' ')  <<std::setw(15) << "Credit Card Exp Date:" << std::setw(12) << card_Expiry_date <<"\n";
	 reciept <<"\t"<< std::setiosflags(std::ios::left)  <<std::setfill(' ')  <<std::setw(15) << "Credit Card Secret Code:"    << std::setw(9) << card_secret_code <<"\n";
	 reciept <<"\t"<< std::setiosflags(std::ios::left) << std::setw(15) << "----Total Item Purchased-----------" << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left) << std::setfill(' ')  <<std::setw(1) << bakedbeans << "x" << " BAKED BEANS."<< std::setw(19) <<(baked_beans * bakedbeans)<<std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left) << std::setfill(' ')  <<std::setw(1) << pop_corn << "x" << " POPCORN."<< std::setw(23) << (popcorn * pop_corn)<<std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left) << std::setfill(' ')  <<std::setw(1) << evaporatedmilk << "x" << " EVAPORATED MILK."<< std::setw(15) << (evaporated_milk * evaporatedmilk) <<std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left) << std::setfill(' ')  <<std::setw(1) << b_read << "x" << " BREAD."<< std::setw(25) << (bread * b_read) << std::endl;;
	 reciept <<"\t"<< std::setiosflags(std::ios::left) << std::setw(15) << "-----------------------------------" <<std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left) << std::setfill(' ')  <<std::setw(1) << "TOTAL COST:" <<std::setw(23) << totalCost << std::endl;
	 //reciept << "\n" << "\t" << "Total Amount:"<< (bakedbeans + pop_corn + evaporatedmilk + b_read) <<std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left) << std::setfill(' ')  <<std::setw(1) << "SALES VAT "<<vat<<":" << std::setw(20) << vat_amount << std::endl;
	 //reciept << "\n" << "\t" << "Total cost: " << totalCost << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left) << std::setfill(' ')  <<std::setw(1) << "FINAL COST:"<< std::setw(23) << finalCost << std::endl;
	 //reciept << "\n" << "\t" << "Total cost: " << ((baked_beans * bakedbeans) + (popcorn * pop_corn) + (evaporated_milk * evaporatedmilk) + (bread * b_read) + vat_amount) << std::endl;
	 reciept <<"\t"<< std::setiosflags(std::ios::left) << std::setw(1) << "-----------------------------------"<<std::endl;
	 reciept << "\t""\t" <<       "  THANK YOU" << std::endl;
	 reciept << "\t" "\t" <<      "HAVE A NICE DAY" << std::endl;


	 
	 reciept.close();
	 if (!reciept)
	 {
		 std::cout << "Error! File cannot be open" << std::endl;
	 }
 }

 int read_from_file()
 {
	 std::string CheckoutSystem = "CheckoutSystem.txt";
	 std::ifstream file;
	 file.open(CheckoutSystem);

	 if (file.is_open())
	 {
		 std::string line;
		 while (std::getline(file, line))
		 {
			 std::cout << line << std::endl;
		 }
		 file.close();
	 }
	 else
	 {
		 std::cout << "Unable to open file " << CheckoutSystem << std::endl;
	 }
	 return 0;

 }
};


int main(int arg, char** argv)
{
	Checkout_sys sys;
	//sys.system_check();
	//sys.get_customer_name();
	//sys.get_customer_address();
	//std::string post_code = "SW15 4JD";
	//sys.isValidPostcode();
	sys.prompt_for_payment();
	//std::string card_ex_date = "11/12/2023";
	sys.isValid_card_expiry_date();
	//std::string card_sec_code = "234";
	//sys.isValidcardSecret_code();
	//sys.list_of_items();
    sys.Calculate_item_quantity();
	sys.write_to_file();
	sys.read_from_file();

	return 0;	
}