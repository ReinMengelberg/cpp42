#include "Bureaucrat.hpp"

static const int	highestGrade = 1;
static const int	lowestGrade = 150;

Bureaucrat::Bureaucrat() : name("nameless"), grade(lowestGrade)
{
	std::cout << "Bureaucrat default constructor called for " << name << "." << std::endl;
}

Bureaucrat::Bureaucrat(const std::string& name, int grade) : name(name), grade(grade)
{
	if (grade < highestGrade)
		throw Bureaucrat::GradeTooHighException();
	if (grade > lowestGrade)
		throw Bureaucrat::GradeTooLowException();
	std::cout << "Bureaucrat constructor called for " << name << "." << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) : name(other.name), grade(other.grade)
{
	std::cout << "Bureaucrat copy constructor called for " << name << "." << std::endl;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	std::cout << "Bureaucrat copy assignment called: " << name << " = " << other.name << "." << std::endl;
	if (this != &other)
		grade = other.grade;
	return *this;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureaucrat destructor called for " << name << "." << std::endl;
}

const std::string& Bureaucrat::getName() const
{
	return name;
}

int Bureaucrat::getGrade() const
{
	return grade;
}

void Bureaucrat::incrementGrade()
{
	if (grade - 1 < highestGrade)
		throw Bureaucrat::GradeTooHighException();
	grade--;
}

void Bureaucrat::decrementGrade()
{
	if (grade + 1 > lowestGrade)
		throw Bureaucrat::GradeTooLowException();
	grade++;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Bureaucrat grade is too high (1 is the highest).";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Bureaucrat grade is too low (150 is the lowest).";
}

std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat)
{
	out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
	return out;
}
