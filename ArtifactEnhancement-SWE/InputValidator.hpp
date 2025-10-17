#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <iostream>
#include <algorithm>
#include <cctype>

/*
		Class to implement input handling and string sanitation.
		Provides a singleton instance for access to functions.
		Requires further implementation to align with Appointment and Task model
		member variables.
*/


class InputValidator {
	private:
		// Hide default constructor and destructor
		InputValidator() {}
		~InputValidator() {}
	public:
		// Delete copy constructor and assignment operator to prevent copies
		InputValidator(const InputValidator&) = delete;
		InputValidator& operator=(const InputValidator&) = delete;

		// Static method to access the singleton instance
		static InputValidator& getInstance()
		{
			static InputValidator instance;
			return instance;
		}

		// Remove any character that is not a-z or A-Z and converts the entire string to lowercase.
		std::string sanitizeName(const std::string& str)
		{
			std::string result;
			for (char c : str) {
				if (std::isalpha(static_cast<unsigned char>(c))) {
					result += std::tolower(static_cast<unsigned char>(c));
				}
			}
			return result;
		}

		// Sanitize strings passed for address, phone number, etc... anything that would be expected to have digits 0-9. 
		// Removes leading/trailing whitespace and converts entire string to lowercase
		std::string sanitizeOther(const std::string& str) 
		{
			std::string strCopy = str;
			auto start = strCopy.begin();
			std::transform(start, strCopy.end(), start, ::tolower);
			while (start != strCopy.end() && std::isspace(*start)) start++;
			return strCopy;
		}

		// Re-format phone number from 01234567890 to 0-123-456-7890
		std::string formatPhoneNumber(const std::string& str)
		{
			return str.substr(0, 1) + "-" +
				str.substr(1, 3) + "-" +
				str.substr(4, 3) + "-" +
				str.substr(7, 4);
		}
};

#endif