#include "AForm.hpp"

static const int	highestGrade = 1;
static const int	lowestGrade = 150;

AForm::AForm() : name("nameless"), isSigned(false), gradeToSign(lowestGrade), gradeToExecute(lowestGrade)
{
	std::cout << "AForm default constructor called for " << name << "." << std::endl;
}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute)
	: name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
	if (gradeToSign < highestGrade || gradeToExecute < highestGrade)
		throw AForm::GradeTooHighException();
	if (gradeToSign > lowestGrade || gradeToExecute > lowestGrade)
		throw AForm::GradeTooLowException();
	std::cout << "AForm constructor called for " << name << "." << std::endl;
}

AForm::AForm(const AForm& other)
	: name(other.name), isSigned(other.isSigned),
	  gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute)
{
	std::cout << "AForm copy constructor called for " << name << "." << std::endl;
}

AForm& AForm::operator=(const AForm& other)
{
	std::cout << "AForm copy assignment called: " << name << " = " << other.name << "." << std::endl;
	if (this != &other)
		isSigned = other.isSigned;
	return *this;
}

AForm::~AForm()
{
	std::cout << "AForm destructor called for " << name << "." << std::endl;
}

const std::string& AForm::getName() const
{
	return name;
}

bool AForm::getIsSigned() const
{
	return isSigned;
}

int AForm::getGradeToSign() const
{
	return gradeToSign;
}

int AForm::getGradeToExecute() const
{
	return gradeToExecute;
}

void AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > gradeToSign)
		throw AForm::GradeTooLowException();
	isSigned = true;
}

void AForm::execute(const Bureaucrat& executor) const
{
	if (!isSigned)
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > gradeToExecute)
		throw AForm::GradeTooLowException();
	action();
}

const char* AForm::GradeTooHighException::what() const throw()
{
	return "the grade is too high (1 is the highest).";
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return "the grade is too low.";
}

const char* AForm::FormNotSignedException::what() const throw()
{
	return "the form is not signed yet.";
}

std::ostream& operator<<(std::ostream& out, const AForm& form)
{
	out << "Form " << form.getName()
		<< " [signed: " << (form.getIsSigned() ? "yes" : "no")
		<< ", grade to sign: " << form.getGradeToSign()
		<< ", grade to execute: " << form.getGradeToExecute() << "]";
	return out;
}
