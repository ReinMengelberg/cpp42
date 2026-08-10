#include "ShrubberyCreationForm.hpp"

#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("ShrubberyCreationForm", 145, 137), target("home")
{
	std::cout << "ShrubberyCreationForm default constructor called for " << target << "." << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
	: AForm("ShrubberyCreationForm", 145, 137), target(target)
{
	std::cout << "ShrubberyCreationForm constructor called for " << target << "." << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
	: AForm(other), target(other.target)
{
	std::cout << "ShrubberyCreationForm copy constructor called for " << target << "." << std::endl;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	std::cout << "ShrubberyCreationForm copy assignment called for " << target << "." << std::endl;
	if (this != &other)
	{
		AForm::operator=(other);
		target = other.target;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "ShrubberyCreationForm destructor called for " << target << "." << std::endl;
}

const std::string& ShrubberyCreationForm::getTarget() const
{
	return target;
}

void ShrubberyCreationForm::action() const
{
	std::ofstream	file((target + "_shrubbery").c_str());

	if (!file.is_open())
	{
		std::cerr << "Error: could not create " << target << "_shrubbery" << std::endl;
		return;
	}
	file << "       ###" << std::endl;
	file << "      #o###" << std::endl;
	file << "    #####o###" << std::endl;
	file << "   #o#\\#|#/###" << std::endl;
	file << "    ###\\|/#o#" << std::endl;
	file << "     # }|{  #" << std::endl;
	file << "       }|{" << std::endl;
	file << std::endl;
	file << "         @" << std::endl;
	file << "       @@@@@" << std::endl;
	file << "     @@@@@@@@@" << std::endl;
	file << "   @@@@@@@@@@@@@" << std::endl;
	file << "        |||" << std::endl;
	file << "        |||" << std::endl;
	file.close();
	std::cout << "Shrubbery planted: " << target << "_shrubbery created." << std::endl;
}
