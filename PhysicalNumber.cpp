#include <iostream>
#include "PhysicalNumber.h"

class FormatException : public std::exception {

	const char* s = 0;
	std::string str;
public:
	FormatException(const ariel::Unit& unit1,const ariel::Unit& unit2) {
		str = "Units don't match - " + ariel::Ename[unit2] + " cannot converted to " + ariel::Ename[unit1];
		s = str.c_str();
	}
	virtual const char* what() const throw(){
		return s;
	}
};
ariel::PhysicalNumber::PhysicalNumber(long double value, ariel::Unit unit) {
	this->value = value;
	this->unit = unit;
}
//ADD and SUB

const ariel::PhysicalNumber ariel::operator+(const ariel::PhysicalNumber & physical)
{
	return PhysicalNumber(+physical.value,physical.unit);
}

const ariel::PhysicalNumber & ariel::operator+=(ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b)
{
	if ((a.unit / 3 == b.unit / 3)) {
		long double num = (a.value * ariel::Enumber[a.unit] + b.value * ariel::Enumber[b.unit]) / ariel::Enumber[a.unit];
		a.value = num;
		return a;
	}
	else throw FormatException(a.unit, b.unit);
}

const ariel::PhysicalNumber ariel::operator+(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b)
{
	if ((a.unit / 3 == b.unit / 3)) {
		long double num = (a.value * Enumber[a.unit] + b.value * Enumber[b.unit]) / Enumber[a.unit];
		return PhysicalNumber(num, a.unit);
	}
	else throw FormatException(a.unit, b.unit);
}
const ariel::PhysicalNumber ariel::operator-(const ariel::PhysicalNumber & physical)
{
	return PhysicalNumber(-physical.value,physical.unit);
}
const ariel::PhysicalNumber & ariel::operator-=(ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b)
{
	if ((a.unit / 3 == b.unit / 3)) {
		long double num = (a.value * ariel::Enumber[a.unit] - b.value * ariel::Enumber[b.unit])/ariel::Enumber[a.unit];
		a.value = num;
		return a;
	}
	else throw FormatException(a.unit, b.unit);
}
ariel::PhysicalNumber ariel::operator--(const ariel::PhysicalNumber & physical)
{
	return PhysicalNumber(physical.value - 1,physical.unit);
}
ariel::PhysicalNumber ariel::operator--(const ariel::PhysicalNumber & physical, int flag)
{
	return PhysicalNumber(physical.value - 1, physical.unit);
}
ariel::PhysicalNumber ariel::operator++(const ariel::PhysicalNumber & physical)
{
	return PhysicalNumber(physical.value + 1, physical.unit);
}
ariel::PhysicalNumber ariel::operator++(const ariel::PhysicalNumber & physical, int flag)
{
	return PhysicalNumber(physical.value + 1, physical.unit);
}
const ariel::PhysicalNumber ariel::operator-(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b)
{
	if ((a.unit / 3 == b.unit / 3)) {
		long double num = (a.value * Enumber[a.unit] - b.value * Enumber[b.unit]) / Enumber[a.unit];
		return PhysicalNumber(num, a.unit);
	}
	else throw FormatException(a.unit,b.unit);
}

//Boolean operators
bool ariel::operator==(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b) {
	if ((a.unit / 3 == b.unit / 3)) {
	return (a.value * Enumber[a.unit]) == (b.value * Enumber[b.unit]);
	}
	else throw FormatException(a.unit,b.unit);
}
bool ariel::operator!=(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b) {
	if ((a.unit / 3 == b.unit / 3)) {
		return !(a==b);
	}
	else throw FormatException(a.unit, b.unit);
}
bool ariel::operator<(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b) {
	if ((a.unit / 3 == b.unit / 3)) {
		return (a.value * Enumber[a.unit]) < (b.value * Enumber[b.unit]);
	}
	else throw FormatException(a.unit, b.unit);
}
bool ariel::operator<=(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b) {

	if ((a.unit / 3 == b.unit / 3)) {
		return (a < b) || (a == b);
	}
	else throw FormatException(a.unit, b.unit);
}
bool ariel::operator>(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b) {
	if ((a.unit / 3 == b.unit / 3)) {
		return (a.value * Enumber[a.unit]) > (b.value * Enumber[b.unit]);
	}
	else throw FormatException(a.unit, b.unit);
}
bool ariel::operator>=(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b) {
	if ((a.unit / 3 == b.unit / 3)) {
		return (a > b) || (a == b);
	}
	else throw FormatException(a.unit, b.unit);
}
//STREAM
std::ostream & ariel::operator<<(std::ostream & os, const ariel::PhysicalNumber & physical)
{
	
	return (os << physical.value << ariel::Ename[physical.unit]);
}
static int get_Enum(std::string name) {
	for (size_t i = 0; i < ariel::Ename.size(); i++)
	{
		if (name.compare(ariel::Ename[i]) == 0) {
			return i;
		}
	}
	return -1;
	
}
std::istream & ariel::operator>>(std::istream & is, ariel::PhysicalNumber & physical)
{
	long double n_value;
	std::string n_unit;
	std::ios::pos_type startPosition = is.tellg();
	is >> n_value >> n_unit;
	int found = get_Enum(n_unit);
	if (found != -1) {
		physical.value = n_value;
		physical.unit = ariel::Unit(found);
	}
	else {
		is.setstate(std::ios::failbit);
		std::cout << "an Invalid Format was given" << std::endl;
		auto errorState = is.rdstate(); // remember error state
		is.clear(); // clear error so seekg will work
		is.seekg(startPosition); // rewind
		is.clear(errorState); // set back the error flag
	}
	return is;
}
