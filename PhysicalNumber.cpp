#include <iostream>
#include <cmath>
#include <limits>
#include "PhysicalNumber.h"

class FormatException : public std::exception {//custom exception for PhysicalNumber

	const char* s = 0;
	std::string str;
public:
	FormatException(const ariel::Unit& unit1,const ariel::Unit& unit2) {//constructor for invalid format change
		str = "Units don't match - " + ariel::Ename[unit2] + " cannot converted to " + ariel::Ename[unit1];
		s = str.c_str();
	}
	virtual const char* what() const throw(){//get cause of exception
		return s;
	}
};
ariel::PhysicalNumber::PhysicalNumber(long double value, ariel::Unit unit) {// PhysicalNumber construtor
	this->value = value;
	this->unit = unit;
}
static void checkFormat(ariel::Unit unitA,ariel::Unit unitB) {//function to check if format is valid 
	if (unitA / 3 == unitB / 3)
		return;
	else throw FormatException(unitA, unitB);
}
//ADD and SUB

const ariel::PhysicalNumber ariel::operator+(const ariel::PhysicalNumber & physical)//+a
{
	return PhysicalNumber(+physical.value,physical.unit);
}

const ariel::PhysicalNumber & ariel::operator+=(ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b)//a = a + b
{
		checkFormat(a.unit, b.unit);
		long double num = (a.value * ariel::Enumber[a.unit] + b.value * ariel::Enumber[b.unit]) / ariel::Enumber[a.unit];
		a.value = num;
		return a;
}

const ariel::PhysicalNumber ariel::operator+(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b)//addition
{
	checkFormat(a.unit, b.unit);
	long double num = (a.value * Enumber[a.unit] + b.value * Enumber[b.unit]) / Enumber[a.unit];
	return PhysicalNumber(num, a.unit);
}
const ariel::PhysicalNumber ariel::operator-(const ariel::PhysicalNumber & physical)//-a
{
	return PhysicalNumber(-physical.value,physical.unit);
}
const ariel::PhysicalNumber & ariel::operator-=(ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b)//a = a - b;
{
	checkFormat(a.unit, b.unit);
	long double num = (a.value * ariel::Enumber[a.unit] - b.value * ariel::Enumber[b.unit])/ariel::Enumber[a.unit];
	a.value = num;
	return a;
}
ariel::PhysicalNumber & ariel::operator--(ariel::PhysicalNumber & physical)//decrement prefix
{
	physical.value--;
	return physical;
}
ariel::PhysicalNumber ariel::operator--(ariel::PhysicalNumber & physical, int flag)//decrement postfix
{
	PhysicalNumber copy = physical;
	physical.value--;
	return copy;
}
ariel::PhysicalNumber & ariel::operator++(ariel::PhysicalNumber & physical)//increment prefix
{
	physical.value++;
	return physical;
}
ariel::PhysicalNumber ariel::operator++(ariel::PhysicalNumber & physical, int flag)//incerment postfix
{
	PhysicalNumber copy = physical;
	physical.value++;
	return copy;
}
const ariel::PhysicalNumber ariel::operator-(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b)//subtraction
{
	checkFormat(a.unit, b.unit);
	long double num = (a.value * Enumber[a.unit] - b.value * Enumber[b.unit]) / Enumber[a.unit];
	return PhysicalNumber(num, a.unit);
}

//Boolean operators
bool ariel::operator==(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b) {//equal
	checkFormat(a.unit, b.unit);
	return std::abs((a.value * Enumber[a.unit]) - (b.value * Enumber[b.unit])) <= std::numeric_limits<long double>::epsilon() * std::abs((a.value * Enumber[a.unit]) + (b.value * Enumber[b.unit])) * 351 || std::abs((a.value * Enumber[a.unit]) + (b.value * Enumber[b.unit])) < std::numeric_limits<long double>::min();// long double is not fully accurate.
}
bool ariel::operator!=(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b) {//not equal
	checkFormat(a.unit, b.unit);
	return !(a==b);
}
bool ariel::operator<(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b) {//lesser then
	checkFormat(a.unit, b.unit);
	return (a.value * Enumber[a.unit]) < (b.value * Enumber[b.unit]);
}
bool ariel::operator<=(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b) {//lesser then or equal
	checkFormat(a.unit, b.unit);
	return (a < b) || (a == b);
}
bool ariel::operator>(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b) {//greater then
	checkFormat(a.unit, b.unit);
	return (a.value * Enumber[a.unit]) > (b.value * Enumber[b.unit]);
}
bool ariel::operator>=(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b) {//greater then or equal
	checkFormat(a.unit, b.unit);
	return (a > b) || (a == b);
}
//STREAM
std::ostream & ariel::operator<<(std::ostream & os, const ariel::PhysicalNumber & physical)// output stream
{
	
	return (os << physical.value << ariel::Ename[physical.unit]);
}
static int get_Enum(std::string name) {//find type by name
	for (size_t i = 0; i < ariel::Ename.size(); i++)
	{
		if (name.compare(ariel::Ename[i]) == 0) {
			return i;
		}
	}
	return -1;
	
}
std::istream & ariel::operator>>(std::istream & is, ariel::PhysicalNumber & physical)//input stream
{
	long double n_value;
	std::string n_unit;
	std::ios::pos_type startPosition = is.tellg();//save postion to rewind to.
	is >> n_value >> n_unit;//get stream variables
	int found = get_Enum(n_unit);
	if (found != -1) {//found unit
		physical.value = n_value;
		physical.unit = ariel::Unit(found);
	}
	else {//failed to find unit
		is.setstate(std::ios::failbit);
		std::cout << "an Invalid Format was given" << std::endl;
		auto errorState = is.rdstate(); // remember error state
		is.clear(); // clear error so seekg will work
		is.seekg(startPosition); // rewind
		is.clear(errorState); // set back the error flag
	}
	return is;
}
