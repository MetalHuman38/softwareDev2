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
#include <limits>
#include <stdio.h>
#include <ctime>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <algorithm>

class CheckoutSystem
/*This class serves as an encapsulation of data and functionality within the program, providing a cohesive unit of organization.It enables the definition of objects with well - defined attributes and behaviors.The class establishes an interface through which data(variables) and member functions can be accessed and manipulated, ensuring encapsulation and data abstraction.*/
{
private:
  std::string shoppers_name;               // Stores the name of the shopper
  std::string address;                     // Stores the address of the shopper
  std::string postcode;                    // Stores the postcode of the shopper
  unsigned long long creditCardNumber = 0; // Stores the credit card number of the shopper (as an unsigned long long)
  char cardType[250];                      // Stores the type of credit card as a character array
  std::string cardExpiryDate;              // Stores the expiry date of the credit card
  std::string cardSecretCode;              // Stores the secret code of the credit card
  double bakedBeansCost = 1.20, popcornCost = 0.80, evaporatedMilkCost = 1.25, breadCost = 2.34;
  // Stores the costs of various items (baked beans, popcorn, evaporated milk, bread)
  float vatRate = 0.20;  // Stores the rate of Value Added Tax (VAT) as a floating-point number
  float totalCost = 0;   // Stores the VAT amount calculated based on the totalCost and vatRate
  float vatAmount = 0;   // Stores the VAT amount calculated based on the totalCost and vatRate
  float finalCost = 0;   // Stores the final cost to be paid (including VAT)
  int totalQuantity = 0; // Stores the total cost of items purchased before VAT
  int bakedBeans = 0, popcorn = 0, evaporatedMilk = 0, bread = 0;
  // Stores the quantities of specific items purchased (baked beans, popcorn, evaporated milk, bread)
  std::ofstream receipt; // Represents the output stream for writing the receipt

public:
  void system_check()
  {
    std::cout << "\n\tWelcome to ASD Supermarket Checkout Point\n";
    std::cout << "\n\tEnter your details below to pay\n";
  }

  bool is_valid_name(const std::string &name)
  {
    // Iterate through each character in the name string
    for (char check : name)
    {
      // Check if the character is not an alphabetic character or a whitespace character
      if (!(std::isalpha(static_cast<unsigned char>(check)) || std::isspace(static_cast<unsigned char>(check))))
      {
        // If an invalid character is found, return false
        return false;
      }
    }
    // If all characters are valid, return true
    return true;
  }

  std::string get_customer_name()
  {

    bool valid_input = false;

    do
    {
      // Prompt the user to enter their first name and last name
      std::cout << "\n\tPlease enter your first name and last name: ";
      // Read the user input and store it in the shoppers_name string
      std::getline(std::cin, shoppers_name);
      // Convert the shoppers_name string to uppercase
      std::transform(shoppers_name.begin(), shoppers_name.end(), shoppers_name.begin(), ::toupper);
      // Print the customer name
      std::cout << "\n\tCustomer name: " << shoppers_name << std::endl;

      // Check if the entered name is valid using the is_valid_name function
      if (!is_valid_name(shoppers_name))
      {
        // If the name is not valid, display an error message
        std::cout << "\n\tError! Name must not include numbers or symbols...\n";
        std::cout << "\n\tPress Enter to continue.......";

        // Clear the input stream and ignore any remaining characters
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      else
      {
        // If the name is valid, set valid_input to true to exit the loop
        valid_input = true;
      }
    } while (!valid_input);

    // Return the valid customer name
    return shoppers_name;
  }

  std::string getValidAddressInput()
  {
    bool isValidInput; // Variable to track if the input is valid or not

    do
    {
      std::cout << "\n\tEnter your address: ";                                    // Prompt the user to enter their address
      std::getline(std::cin, address);                                            // Read the input from the user and store it in the variable 'address'
      std::transform(address.begin(), address.end(), address.begin(), ::toupper); // Convert the address to uppercase

      std::cout << "\n\tCustomer address: " << address << std::endl; // Display the entered address to the user

      isValidInput = true; // Assume the input is valid initially

      for (char check : address) // Iterate over each character in the address
      {
        if (!(std::isalpha(static_cast<unsigned char>(check)) || // Check if the character is an alphabet
              std::isspace(static_cast<unsigned char>(check)) || // or a whitespace
              std::isdigit(static_cast<unsigned char>(check))))  // or a digit
        {
          isValidInput = false; // If the character is not valid, set the flag to false
          std::cerr << "\n\tInvalid input! Type in your address without symbols, commas, or dots.\n";
          std::cout << "\n\tPress Enter to continue.......";                  // Prompt the user to press Enter to continue
          std::cin.clear();                                                   // Clear any error flags
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining input

          break; // Exit the loop
        }
      }
    } while (!isValidInput); // Repeat the loop until a valid input is entered

    return address; // Return the validated address
  }

  bool isValidPostcode() // Function to check if a postcode is valid
  {
    std::regex pattern("^[a-zA-Z]{1,2}[0-9]{1,2}[a-zA-Z]?(\\s*[0-9][a-zA-Z]{1,2})?$");

    while (true)
    {
      // Prompt the user to enter the postcode
      std::cout << "\n\tEnter your postcode: ";
      std::getline(std::cin, postcode); // Read the input from the user and store it in the variable 'postcode'

      std::transform(postcode.begin(), postcode.end(), postcode.begin(), ::toupper); // Convert the postcode to uppercase
      bool match = std::regex_match(postcode, pattern);                              // Check if the postcode matches the pattern using regular expressions

      if (!match)
      {
        // Display an error message if the postcode is invalid
        std::cerr << "\n\tInvalid PostCode! Correct Format example(SW15 4JD). Try again\n";
        std::cout << "\n\tPress Enter to continue.......";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      else
      {
        // Display the valid postcode and return true
        std::cout << "\n\tPost Code: " << postcode << std::endl;
        return match;
      }
    }
  }

  std::string prompt_for_payment() // Function to accept user payment.
  {
    // Prompts user for credit card number.
    std::cout << "\n\tEnter your credit card number: ";
    std::cin >> creditCardNumber; // Read the input from the user and store it in the variable 'creditCardNumber'

    // Check if the entered credit card number is valid
    while (std::cin.fail() || std::to_string(creditCardNumber).length() < 10 ||
           std::to_string(creditCardNumber).length() > 19)
    {
      // Clear input flags and ignore any remaining input.
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      // Display an error message for an invalid credit card number
      std::cout << "\n\tError! Please use a numeric value with a minimum of 10 digits and not more than 16digits." << std::endl;

      // Prompt user again until valid input.
      std::cout << "\n\tEnter your credit card number: ";
      std::cin >> creditCardNumber;
    }

    // Display the valid Credit Card number.
    std::cout << "\n\tCredit Card number: " << creditCardNumber << std::endl;

    if (isCardNumberValid(creditCardNumber))
    {
      // Get the type of the valid credit card
      std::string cardType = getCardType(creditCardNumber);
      std::cout << "\n\tValid" << std::endl;
      std::cout << "\n\tCredit Card Type: " << cardType;
      return cardType;
    }
    else
    {
      // Display invalid if the numbers of digit enter passes the input validation but not a valid credit card.
      std::cout << "\n\tInvalid Card" << std::endl;
      return "Invalid Card";
    }
  }

  bool isCardNumberValid(unsigned long long creditCardNumber) // Checks if the credit card number is valid using the Luhn algorithm.
  {
    return isLuhnValid(creditCardNumber);
  }

  bool isLuhnValid(unsigned long long creditCardNumber) // Implements the Luhn algorithm to check if a credit card number is valid.
  {
    int sum = 0;            // Initialize the sum to 0
    bool alternate = false; // Indicates whether to double every other digit

    while (creditCardNumber > 0) // The code enters a loop that iterates through each digit of the credit card number.
    {
      int digit = creditCardNumber % 10; // Inside the loop, it extracts the last digit of the number using the modulo operator % and assigns it to the digit variable.

      if (alternate) // Double the digit if alternate is true
      {
        digit *= 2;
        if (digit > 9) // If the alternate flag is true, the digit is doubled. If the doubled digit is greater than 9, it subtracts 9 to handle two-digit results.
          digit -= 9;
      }

      sum += digit;           // The doubled or original digit is added to the running sum
      alternate = !alternate; // Toggle the alternate flag for the next iteration (i.e., flipped to the opposite value) to handle alternating doubling.
      creditCardNumber /= 10; // The last digit is removed from the credit card number by dividing it by 10.
    }

    return (sum % 10 == 0); // Return true if the sum is divisible by 10 (valid Luhn check digit)
  }

  std::string getCardType(unsigned long long creditCardNumber) // The function takes an unsigned long long creditCardNumber as input and returns a string representing the card type.
  {
    // std::string cardType = "Unknown";
    int numDigits = std::to_string(creditCardNumber).length(); // It determines the number of digits in the credit card number by converting it to a string using std::to_string() and calculating the length.

    if (numDigits == 13 || numDigits == 16) // Check if the number of digits is 13 or 16
    {
      if (creditCardNumber / 1000000000000ULL == 4)
        strcpy(cardType, "VISA"); // Set the card type to "VISA" if the first digit is 4
      else if (creditCardNumber / 10000000000000ULL == 34 || creditCardNumber / 10000000000000ULL == 37)
        strcpy(cardType, "AMERICAN EXPRESS"); // Set the card type to "AMERICAN EXPRESS" if the first two digit is 34 OR 37.
      else if (creditCardNumber / 100000000000000ULL >= 50 && creditCardNumber / 100000000000000ULL <= 55)
        strcpy(cardType, "MASTERCARD"); // Set the card type to "MASTERCARD" if the first two digits are between 50 and 55 (inclusive)
      else if (creditCardNumber / 1000000000000ULL == 6011)
        strcpy(cardType, "DISCOVERY CARD"); // Set the card type to "DISCOVERY CARD" if the first four digits are 6011
    }

    return cardType; // Return the determined card type
  }

  bool isValidCardExpiryDate() // Function uses a regular expression pattern to define the valid format for the credit card expiry date. The pattern allows for dates in the format of DD/MM/YYYY or DD-MM-YYYY or DD.MM.YYYY.
  {

    std::regex pattern("^([0]?[1-9]|[1|2][0-9]|[3][0|1])[./-]([0]?[1-9]|[1][0-2])[./-]([0-9]{4}|[0-9]{2})$");

    while (true)
    {
      // Prompt the user to enter the credit card expiry date
      std::cout << "\n\tEnter Credit Card Expiry Date in DD/MM/YYYY format: ";
      std::cin >> cardExpiryDate;

      if (!std::regex_match(cardExpiryDate, pattern)) // Check if the entered date matches the pattern
      {
        // Clear input flags and ignore any remaining input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Display an error message for invalid date format
        std::cerr << "\n\tInvalid Date format! Enter a valid date in dd/mm/yyyy format: ";
      }
      else
      {
        // Display the valid credit card expiry date
        std::cout << "\n\tCredit Card Expiry Date: " << cardExpiryDate << std::endl;
        return true; // Return true to indicate successful validation
      }
    }
  }

  bool isValidCardSecretCode() // Function uses a regular expression pattern to define the valid format for the secret code, consisting of 3 or 4 digits.
  {
    // Define the regular expression pattern for valid secret codes (consisting of 3 or 4 digits)
    std::regex pattern("^[0-9]{3,4}$");

    while (true) // function enters an infinite loop using while (true) to repeatedly prompt the user to enter a credit card secret code.
    {
      // Prompt the user to enter the credit card secret code
      std::cout << "\n\tEnter Credit Card Secret Code: ";
      std::cin >> cardSecretCode; // Read from the user using std::cin and stored in the cardSecretCode variable.

      if (!std::regex_match(cardSecretCode, pattern)) // Check if the entered code matches the pattern
      {
        // Clear input flags and ignore any remaining input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // Display an error message for invalid entry
        std::cout << "\n\tInvalid Entry!";
        std::cout << "\n\tEnter numbers not less than three and not more than four: ";
      }
      else
      {
        // Display the valid credit card secret code
        std::cout << "\n\tCredit Card Secret Code: " << cardSecretCode << std::endl;
        return true; // Return true to indicate successful validation
      }
    }
  }

  void list_of_items()
  {
    // Display the list of items and their respective unit prices
    std::cout << "\n\t=== The Unit Price for Items ===" << std::endl;
    std::cout << "\n\t  Baked Beans:     £1.20" << std::endl;
    std::cout << "\n\t  Popcorn:         £0.80" << std::endl;
    std::cout << "\n\t  Evaporated Milk: £1.15" << std::endl;
    std::cout << "\n\t  Bread:           £2.20" << std::endl;
  }

  double calculateItemQuantity()
  {

    bool validInput = false; // Flag to track the validity of user input

    do
    {
      // Prompt the user to enter the quantities of items purchased
      std::cout << "\n\tEnter the quantity of Baked Beans purchased: ";
      std::cin >> bakedBeans;
      std::cout << "\n\tEnter the quantity of Popcorn purchased: ";
      std::cin >> popcorn;
      std::cout << "\n\tEnter the quantity of Evaporated Milk purchased: ";
      std::cin >> evaporatedMilk;
      std::cout << "\n\tEnter the quantity of Bread purchased: ";
      std::cin >> bread;

      if (std::cin.fail()) // Check if the input is invalid (non-numeric)
      {
        std::cin.clear();                                                   // Clear the fail state of cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining input

        // Display an error message for invalid input
        std::cout << "\n\tInvalid input! Please enter a numeric value.\n";
      }
      else if (bakedBeans >= 1 || popcorn >= 1 || evaporatedMilk >= 1 || bread >= 1)
      {
        validInput = true; // Set the flag to indicate valid input.

        // Display the total items purchased
        std::cout << "\n\t==== Total Items Purchased ====\n";
        std::cout << "\n\t" << bakedBeans << " Baked Beans";
        std::cout << "\n\t" << popcorn << " Popcorn";
        std::cout << "\n\t" << evaporatedMilk << " Evaporated Milk";
        std::cout << "\n\t" << bread << " Bread\n";

        totalQuantity = (bakedBeans + popcorn + evaporatedMilk + bread); // Calculate the total quantity of items
        std::cout << "\n\tTotal Quantity: " << totalQuantity << std::endl;

        totalCost = ((bakedBeansCost * bakedBeans) + (popcornCost * popcorn) +
                     (evaporatedMilkCost * evaporatedMilk) + (breadCost * bread)); // Calculate the total cost of items
        std::cout << "\n\tTotal Cost: " << totalCost << std::endl;

        vatAmount = totalCost * vatRate; // Calculate the VAT amount
        std::cout << "\n\tSales VAT: " << vatAmount << std::endl;

        finalCost = totalCost + vatAmount; // Calculate the final cost including VAT
        std::cout << "\n\tFinal Cost: " << finalCost << std::endl;

        return finalCost; // Return the final cost
      }
      else
      {
        std::cin.clear();                                                   // Clear the fail state of cin.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining input.

        // Display an error message for invalid input
        std::cout << "\n\tEnter a number greater than zero to process the purchase.\n";
      }
    } while (!validInput);

    return 0.0; // Default return value if no valid input is provided
  }

  void writeLine(std::ofstream &receipt, const std::string &label, const std::string &value, int width, int precision = -1)
  {
    // This a helper function that Write a line to the receipt file with the specified label, value, and width. The line is formatted with left alignment and the specified width.
    if (precision != -1)
    {
      receipt << std::setiosflags(std::ios::fixed) << std::setprecision(precision);
    }
    receipt << "\t" << std::setiosflags(std::ios::left) << std::setw(width) << label << value << "\n";
    receipt << std::setiosflags(std::ios::fixed) << std::setprecision(2);
  }

  void
  writeSection(std::ofstream &receipt, const std::string &label)
  {
    receipt << "\t" << std::setiosflags(std::ios::left) << std::setw(15) << label << std::endl;
    // Helper function Writes a section header to the receipt file with the specified label. The section header is formatted with left alignment and a fixed width of 15.
  }

  void write_to_file()
  {

    std::ofstream receipt{"CheckoutSystem.txt", std::ofstream::out}; // Create an output file stream object named "receipt" and open the file "CheckoutSystem.txt" for writing.

    receipt << std::fixed; // Set the floating-point output format to fixed.
    if (receipt.is_open())

    {
      receipt << std::fixed << std::setprecision(2) << totalQuantity << totalCost << vatAmount << finalCost << std::endl;
      // Write the total quantity, total cost, VAT amount, and final cost to the "receipt" file.
      // The values are formatted with fixed-point notation and a precision of 2 decimal places.

      receipt << "\t" << std::setiosflags(std::ios::left) << std::setw(15) << "*******SHOP RECEIPT**************" << std::endl;
      // Write a section header for the shop receipt title to the "receipt" file.
      // The header is formatted with left alignment and a width of 15 characters.
      receipt << "\t" << std::setiosflags(std::ios::right) << std::setw(15) << "ADS SUPERMARKET" << std::endl;
      // Write the supermarket name to the "receipt" file.
      // The name is formatted with right alignment and a width of 15 characters.
      receipt << "\t" << std::setiosflags(std::ios::right) << std::setw(17) << "10,CARD LANE,LONDON. SW19 4UD " << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setw(17) << "Tel:                 01483-220494 " << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setw(14) << "RECEIPT NO:          01654" << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setw(17) << "DATE:                15/05/2023   " << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setw(17) << "CASHIER:             JOHN DOE  " << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setw(15) << "------------------------------------" << std::endl;

      writeLine(receipt, "NAME:            ", shoppers_name, 5, 15);
      // Write the shopper's name to the "receipt" file using the "writeLine" function.
      // The label is "NAME:            ", and the value is provided by the "shoppers_name" variable.
      // The line is formatted with a width of 5 characters.
      writeLine(receipt, "ADDRESS:     ", address, 1, 15);
      writeLine(receipt, "POSTCODE:                 ", postcode, 5, 15);
      writeLine(receipt, "CREDIT CARD No:     ", std::to_string(creditCardNumber), 15, 2);
      writeLine(receipt, "Valid", "", 1);
      writeLine(receipt, "Credit Card Type:      ", cardType, 15, 15);

      receipt << "\t" << std::setiosflags(std::ios::left) << std::setfill(' ')
              << std::setw(15) << "CREDIT CARD EXP DATE:"
              << std::setw(15) << cardExpiryDate
              << std::endl;
      // Write the label "CREDIT CARD EXP DATE:" followed by the value of "cardExpiryDate" to the "receipt" file.
      // The line is formatted with a width of 15 characters for the label and the value.
      // The line is left-aligned and padded with empty spaces. The same applies to the rest of the code.
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setfill(' ')
              << std::setw(15) << "CREDIT CARD SECRET CODE:"
              << std::setw(12) << cardSecretCode
              << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setw(15) << "----Total Item Purchased-------------" << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setfill(' ') << std::setw(1) << bakedBeans << " BAKED BEANS" << std::setw(20) << "£" << (bakedBeansCost * bakedBeans) << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setfill(' ') << std::setw(1) << popcorn << " POPCORN" << std::setw(24) << "£" << (popcornCost * popcorn) << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setfill(' ') << std::setw(1) << evaporatedMilk << " EVAPORATED MILK" << std::setw(16) << "£" << (evaporatedMilkCost * evaporatedMilk) << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setfill(' ') << std::setw(1) << bread << " BREAD" << std::setw(26) << "£" << (breadCost * bread) << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setw(15) << "-------------------------------------" << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setfill(' ') << std::setw(1) << "TOTAL QUANTITY:" << std::setw(21) << totalQuantity << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setfill(' ') << std::setw(1) << "TOTAL COST:" << std::setw(21) << "£" << totalCost << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setfill(' ') << std::setw(1) << "SALES VAT " << vatRate << ":" << std::setw(18) << "£" << vatAmount << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setfill(' ') << std::setw(1) << "FINAL COST:" << std::setw(21) << "£" << std::setiosflags(std::ios::fixed) << std::setprecision(2) << finalCost << std::endl;
      receipt << "\t" << std::setiosflags(std::ios::left) << std::setw(1) << "-------------------------------------" << std::endl;
      receipt << "\t"
                 "\t"
              << "  THANK YOU" << std::endl;
      receipt << "\t"
                 "\t"
              << "HAVE A NICE DAY" << std::endl;
      receipt.close(); // Close the "receipt" file after writing all the contents.
    }
    else if (!receipt) // If the "receipt" file failed to open, display an error message indicating that the file cannot be opened.
    {
      std::cout << "Error! File cannot be open" << std::endl;
    }
  }

  int read_from_file() /*Function reads from file and output values(receipt) to console*/
  {
    std::string CheckoutSystem = "CheckoutSystem.txt"; // Store the name of the file to be read as "CheckoutSystem".
    std::ifstream file;                                // Declare an input file stream object.
    file.open(CheckoutSystem);                         // Open the file with the name "CheckoutSystem".

    if (file.is_open()) // If the file is successfully opened:
    {

      std::string line;                // Declare a string variable to store each line of the file.
      while (std::getline(file, line)) // Read each line from the file and store it in the "line" variable.
      {

        std::cout << line << std::endl; // Output the contents of the "line" variable to the console.
      }
      file.close(); // Close the file after reading.
    }
    else
    {
      // If the file failed to open:
      std::cout << "Unable to open file " << CheckoutSystem << std::endl; // Display an error message indicating the inability to open the file.
    }
    return 0; // Return 0 to indicate successful execution of the function.
  }
};
int main()
{
  CheckoutSystem sys;
  sys.system_check();
  sys.get_customer_name();
  sys.getValidAddressInput();
  sys.isValidPostcode();
  sys.prompt_for_payment();
  sys.isValidCardExpiryDate();
  sys.isValidCardSecretCode();
  sys.list_of_items();
  sys.calculateItemQuantity();
  sys.write_to_file();
  sys.read_from_file();
}
