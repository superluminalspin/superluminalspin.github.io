#include <iostream>
#include "Contact.hpp"
#include "ContactService.hpp"
#include "InputValidator.hpp"
#include <vector>


static void DisplayMenu() {
	std::cout << "\n1. Add new contact contact\n2. Update existing contact\n";
	std::cout << "3. Remove existing contact\n4. Print Contacts\n0. Return to main menu\n";
	std::cout << "**********************\n";
	std::cout << "Choose an option\n";
};

static std::string GetValidatedId() {
	std::string input;
	while (true) {
		std::cout << "Enter contact's 4-digit ID number -- 0 to exit: ";
		std::getline(std::cin, input);

		if (input == "0") {
			throw std::runtime_error("User cancelled");
		}

		if (input.size() != 4 || !ContactService::getInstance().contacts.contains(input)) {
			std::cout << "ID number is invalid." << std::endl;
			continue;
		}

		return input;
	}

};

std::string GetValidatedInput(const std::string& prompt, int maxLength) {
	std::string input;
	while (true) {
		std::cout << prompt << " -- 0 to exit: ";
		std::getline(std::cin, input);

		if (input == "0") {
			std::cout << "Returning to menu." << std::endl;
			return "0"; // Let caller handle this
		}
		else if (input.length() <= maxLength && input.length() > 0) {
			return input;
		}
		else {
			std::cout << "Invalid input length" << std::endl;
		}
	}
}

void ContactManager() 
{
	bool outerLoopControl = true;

	while (outerLoopControl) {

		DisplayMenu();

		int condition = -1;

		std::string input = "";
		std::string id = "";
		std::string temp = "";
		std::string str = "";
		std::vector<std::string> inputList;

		
		const Contact* contact;

		std::cin >> condition;

		switch (condition) {
			
		// Add Contact
		case 1:
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			// First Name
			input = GetValidatedInput("\nEnter first name (up to 50 characters)", 50);
			if (input == "0") return;
			str = InputValidator::getInstance().sanitizeName(input);
			inputList.push_back(str);

			// Last Name  
			input = GetValidatedInput("\nEnter last name (up to 50 characters)", 50);
			if (input == "0") return;
			str = InputValidator::getInstance().sanitizeName(input);
			inputList.push_back(str);


			// Phone Number
			while (true) {
				input = GetValidatedInput("\nEnter phone number (ex. 12124567890)", 11);
				if (input == "0") return;
				if (input.length() == 11) {
					temp = InputValidator::getInstance().sanitizeOther(input);
					temp = InputValidator::getInstance().formatPhoneNumber(temp);
					inputList.push_back(temp);
					std::cout << temp << std::endl;
					break;
				}
				else {
					std::cout << "Invalid input length" << std::endl;
				}
			}

			// Address
			input = GetValidatedInput("\nEnter address (up to 200 characters)", 200);
			if (input == "0") return;
			temp = InputValidator::getInstance().sanitizeOther(input);
			inputList.push_back(temp);
			std::cout << temp << std::endl;

			contact = new Contact(inputList.at(0), inputList.at(1), inputList.at(2), inputList.at(3));
			ContactService::getInstance().addContact(*contact);

			break;

		// Update Contact
		case 2:
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			id = GetValidatedId();

			// First Name
			input = GetValidatedInput("\nEnter first name (up to 50 characters)", 50);
			if (input == "0") return;
			str = InputValidator::getInstance().sanitizeName(input);
			inputList.push_back(str);

			// Last Name  
			input = GetValidatedInput("\nEnter last name (up to 50 characters)", 50);
			if (input == "0") return;
			str = InputValidator::getInstance().sanitizeName(input);
			inputList.push_back(str);


			// Phone Number
			while (true) {
				input = GetValidatedInput("\nEnter phone number (ex. 12124567890)", 11);
				if (input == "0") return;
				if (input.length() == 11) {
					temp = InputValidator::getInstance().sanitizeOther(input);
					temp = InputValidator::getInstance().formatPhoneNumber(temp);
					inputList.push_back(temp);
					std::cout << temp << std::endl;
					break;
				}
				else {
					std::cout << "Invalid input length" << std::endl;
				}
			}

			// Address
			input = GetValidatedInput("\nEnter address (up to 200 characters)", 200);
			if (input == "0") return;
			temp = InputValidator::getInstance().sanitizeOther(input);
			inputList.push_back(temp);
			std::cout << temp << std::endl;

			contact = new Contact(id, inputList.at(0), inputList.at(1), inputList.at(2), inputList.at(3));

			ContactService::getInstance().updateContact(contact->getId(), *contact);

			break;

		// Remove Contact
		case 3:
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (ContactService::getInstance().contacts.size() == 0) {
				std::cout << "No contacts to remove." << std::endl;
				return;
			}

			id = GetValidatedId();
			ContactService::getInstance().deleteContact(id);
			std::cout << "Contact " + id + " has been successfully removed." << std::endl;

			break;
		// Print Contacts
		case 4:
			if (ContactService::getInstance().contacts.size() == 0) {
				std::cout << "No contacts exist.\n";
			}
			for (const auto& pair : ContactService::getInstance().contacts) {
				std::cout << pair.second.toString();
			}
			break;
		case 0:
			std::cout << "\nReturning to main menu\n" << std::endl;
			outerLoopControl = false;
			break;
		default:
			break;
		}

	}
}


int main() 
{

	// Loop control variable
	bool loopControl = true;

	// Application loop
	while (loopControl) {
		std::cout << "   Appointment Book\n**********************\n";
		std::cout << "1. Contact Manager\n2. Task Manager\n3. Appointment Manager\n0. Exit\n**********************\n";

		int condition = -1;
		
		std::cout << "Choose an option: ";
		std::cin >> condition;

		switch (condition)
		{
			case 1:
				std::cout << "\nEntering Contact Manager" << std::endl;
				ContactManager();
				break;
			case 2:
				std::cout << "2" << std::endl;
				break;
			case 3:
				std::cout << "3" << std::endl;
				break;
			case 0:
				loopControl = false;
				std::cout << "\nExiting program." << std::endl;
				break;
		}
	}

	return 0;
}