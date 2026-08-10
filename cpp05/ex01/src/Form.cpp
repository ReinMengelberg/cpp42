#include "Form.hpp"

static const int	highestGrade = 1;
static const int	lowestGrade = 150;

Form::Form() : name("nameless"), isSigned(false), gradeToSign(lowestGrade), gradeToExecute(lowestGrade)
{
	std::cout << "Form default constructor called for " << name << "." << std::endl;
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
	: name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
	if (gradeToSign < highestGrade || gradeToExecute < highestGrade)
		throw Form::GradeTooHighException();
	if (gradeToSign > lowestGrade || gradeToExecute > lowestGrade)
		throw Form::GradeTooLowException();
	std::cout << "Form constructor called for " << name << "." << std::endl;
}

Form::Form(const Form& other)
	: name(other.name), isSigned(other.isSigned),
	  gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute)
{
	std::cout << "Form copy constructor called for " << name << "." << std::endl;
}

Form& Form::operator=(const Form& other)
{
	std::cout << "Form copy assignment called: " << name << " = " << other.name << "." << std::endl;
	if (this != &other)
		isSigned = other.isSigned;
	return *this;
}

Form::~Form()
{
	std::cout << "Form destructor called for " << name << "." << std::endl;
}

const std::string& Form::getName() const
{
	return name;
}

bool Form::getIsSigned() const
{
	return isSigned;
}

int Form::getGradeToSign() const
{
	return gradeToSign;
}

int Form::getGradeToExecute() const
{
	return gradeToExecute;
}

void Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > gradeToSign)
		throw Form::GradeTooLowException();
	isSigned = true;
}

const char* Form::GradeTooHighException::what() const throw()
{
	return "the grade is too high (1 is the highest).";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "the grade is too low.";
}

std::ostream& operator<<(std::ostream& out, const Form& form)
{
	out << "Form " << form.getName()
		<< " [signed: " << (form.getIsSigned() ? "yes" : "no")
		<< ", grade to sign: " << form.getGradeToSign()
		<< ", grade to execute: " << form.getGradeToExecute() << "]";
	return out;
}
