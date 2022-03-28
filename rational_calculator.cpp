// FCAI – Programming 1 – 2022 - Assignment 2
// Program Name: Rational_Calculator_20210268_20210324_20210241.cpp
// Program Description: A rational number calculator
// Last Modification Date: 27/03/2022
// Author1 and ID and Group: Omar Ezz El-Deen, 20210268, Group A
// Author2 and ID and Group: Mohamed Ahmed Fathy, 20210324, Group A
// Author3 and ID and Group: Aly Ahmed Salah, 20210241, Group A
// Teaching Assistant: xxxxx xxxxx
// Purpose: Assignment 2

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

bool valid(std::string input, char ope)           // function to check if the operation is valid  (1st function to be performed)
{
	if (ope == '/' || ope == '*' || ope == '+' || ope == '-') {     // makes sure the operator inputted is valid
		for (int i = 0; i < input.length(); i++) { 
			
			if (isgraph(input[i]) && !isdigit(input[i]) && input[i] != ope && input[i] != '-' && input[i] != '/') {
				return false;  // if any character is not a number or the operator or the negative sign or '/', the operation isn't valid
			} 
		}
	}
	else {
		return false;    // if the operator is not of the basic operators, the operation isn't valid
	}
	return true;
}

bool num_valid(std::string input)    // function to check if each term is valid   (3rd function to be performed)
{
	if (input[0] == '/' || ispunct(input[input.length()])) {    // make sure that the term starts and ends with an integer
		return false;
	}
	else if (!isdigit(input[input.find('/') - 1]) || !isdigit(input[input.find('/') + 1]) || input[input.find('/') + 1] == '0') {
		return false;           // make sure that before and after the '/' there is a number
	}
	return true;
}

int simple(int nom, int denom)     // function to simplify the result   (7th function to be performed)
{
	int low;
	if (denom < 0) {       // if the denominator is negative, move the negative sign to the nominator
		nom *= -1;
		denom *= -1;
	}

	if (denom < nom || nom < 0) {    // see which of the nominator or denominator is lower to use in GCD
		low = denom;
	}
	else {
		low = nom;
	}

	for (int i = low; i > 0; i--) {
		if (nom % i == 0 && denom % i == 0) {    // find the GCD (greatest common divisor) and simplify the final result
			nom /= i;
			denom /= i;
			break;
		}
	}

	if (denom != 1 && nom != 0) {
		if (denom > nom) {
			std::cout << "= " << nom << '/' << denom << '\n';    // if there is no more simplification, print the result in the form a/b
		}
		else {    // if the nominator is bigger than the denominator, print the result in the mixed form (a b/c)
			std::cout << "= " << nom / denom << " " << nom - (denom * (nom/denom)) << "/" << denom << '\n';
		}
	}
	else {
		std::cout << "= " << nom << '\n';     // if the denominator of the result is 1 or the nominator is 0, print the result as whole number
	}
	return 0;
}

int number1(std::string sub)      //function to get the nominator of the fraction  (4th function to be performed)
{
	float i = sub.find('/');
	int num1 = stoi(sub.substr(0, i));    //turn the number before the '/' into an integer
	return num1;
}

int number2(std::string sub)     // function to get the denominator of the fraction  (5th function to be performed)
{
	float i = sub.find('/');
	int num2 = stoi(sub.substr(i + 1, sub.length() - i - 1));    // turn the number after the '/' into an integer
	return num2;
}

int multiply(int num1, int num2, int num3, int num4)     // function to multiply   (6th function to be performed)
{
	int nom = num1 * num3;     // get the nominator of the result 
	int denom = num2 * num4;   // get the denominator of the result
	simple(nom, denom);        // simplify the result
	return 0;
}

int divide(int num1, int num2, int num3, int num4)    // function to divide    (6th function to be performed)
{ 
	int nom = num1 * num4;        // get the nominator of the result 
	int denom = num2 * num3;      // get the denominator of the result
	simple(nom, denom);           // simplify the result
	return 0;
}

int plus(int num1, int num2, int num3, int num4)        // function to add  (6th function to be performed)
{
	int denom = num2 * num4;            // get the denominator of the result
	int nom = (num1 * num4) + (num3 * num2);    // get the nominator of the result
	simple(nom, denom);          // simplify the result
	return 0;
}

int minus(int num1, int num2, int num3, int num4)    // function to subtract  (6th function to be performed)
{
	int denom = num2 * num4;                // get the denominator of the result
	int nom = (num1 * num4) - (num3 * num2);    // get the nominator of the result
	simple(nom, denom);           // simplify the result
	return 0;
}

int split(char ope, std::string input)       // function to split the operation into two terms   (2nd function to be performed)
{
	std::string sub1, sub2;
	int num1, num2, num3, num4;
	float i = input.find_first_not_of(' ', input.find(' '));     // find the index of the operator
	
	sub1 = input.substr(0, i);       // the first term is from index 0 to the index of the operator
	sub2 = input.substr(i + 1, input.length() - i);    // the second term is from the index after the operator to the end


	if (sub1.find('/') == -1) {        // if the first term is a whole number
		num1 = stoi(sub1), num2 = 1;  // set the denominator to 1
	}
	else {                             // if the first term is a fraction
		if (!num_valid(sub1)) {        // check if the term is valid
			std::cout << "Invalid operation. Try again.\n";  // if not, ask the user to try again and exit from the function
			return 0;
		}
		num1 = number1(sub1), num2 = number2(sub1);   // if it is valid, turn the nominator and denominator to integers
	}
	
	
	if (sub2.find('/') == -1) {     // if the second term is a whole number
		num3 = stoi(sub2), num4 = 1;   // set the denominator to 1
	}
	else {                           // if the second term is a fraction
		if (!num_valid(sub2)) {         // check if the term is valid
			std::cout << "Invalid operation. Try again.\n";  // if not, ask the user to try again and exit from the function
			return 0;
		}
		num3 = number1(sub2), num4 = number2(sub2);   // if it is valid, turn the nominator and denominator to integers
	}
	

	switch (ope) {        // check which operation to perform
	case '*':
		multiply(num1, num2, num3, num4);   // multiplication
		break;
	case '/':
		if (num3 == 0) {            // if the second term equals 0, ask the user to try again and exit from the function
			std::cout << "Invalid operation. Try again.\n";
			return 0;
		}
		divide(num1, num2, num3, num4);    // dividing
		break;
	case '+':
		plus(num1, num2, num3, num4);     // addition
		break;
	case '-':
		minus(num1, num2, num3, num4);    // subtraction
	}
	return 0;
}

int main()               
{
	std::string input = "input";
	char ope;
	bool isValid = true;                   // the input should be in the form (a/b   'ope'   c/d), if not we ask the user to try again
	std::cout << "Enter a rational number operation with space between the main operator and the numbers (or type exit)\n";
	
	while (input != "exit" && input != "Exit" && input != "EXIT") {        // once the user enters "exit" the while loop ends
		std::cout << ">> ";
		getline(std::cin, input);
		input.erase(input.find_last_not_of(' ') + 1);                      // removes white space from the right of the input
		input.erase(0, input.find_first_not_of(' '));                      // removes white space from the left of the input
		if (input == "exit" || input == "Exit" || input == "EXIT") {       // if the user enters "exit" don't continue
			break;
		}
		
		if (input.find(' ') == -1) {              
			ope = 'n';
		}
		else {
			ope = input[input.find_first_not_of(' ', input.find(' '))];   // set the operator to the character after the first space
		}                                                                                // example: (a/b   +   c/d)
		
		isValid = valid(input, ope);                      // check if the operation is valid (using the function)
		if (!isValid || !isspace(input[input.find_first_not_of(' ', input.find(' ')) + 1])) {   // if not valid, ask the user to try again
			std::cout << "Invalid operation. Try again.\n";
			continue;
		}
		split(ope , input);          // if valid, split the operation at the operator
	}
	std::cout << "Thanks for using the application\n";
	return 0;
}