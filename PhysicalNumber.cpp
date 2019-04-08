#include <iostream>
#include "PhysicalNumber.h"

class FormatException : public std::exception {

	const char* s = 0;
	std::string str;
public:
	
	FormatException(const std::string name) {
		str = "Incorret unit format couldn't resolve what " + name + " means...";
		s = str.c_str();
	}
	FormatException(const ariel::Unit& unit1,const ariel::Unit& unit2) {
		str = "Units don't match - " + ariel::Ename[unit2] + " cannot converted to " + ariel::Ename[unit1];
		s = str.c_str();
	}
	virtual const char* what() const throw(){
		return s;
	}
};

using ariel::PhysicalNumber;

PhysicalNumber::PhysicalNumber(long double value, ariel::Unit unit) {
	this->value = value;
	this->unit = unit;
}
//ADD and SUB

const PhysicalNumber ariel::operator+(const ariel::PhysicalNumber & physical)
{
	return PhysicalNumber(+physical.value,physical.unit);
}

const PhysicalNumber & ariel::operator+=(ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b)
{
	if ((a.unit / 3 == b.unit / 3)) {
		long double num = (a.value * ariel::Enumber[a.unit] + b.value * ariel::Enumber[b.unit]) / ariel::Enumber[a.unit];
		a.value = num;
		return a;
	}
	else throw FormatException(a.unit, b.unit);
}

const PhysicalNumber ariel::operator+(const ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b)
{
	if ((a.unit / 3 == b.unit / 3)) {
		long double num = (a.value * Enumber[a.unit] + b.value * Enumber[b.unit]) / Enumber[a.unit];
		return PhysicalNumber(num, a.unit);
	}
	else throw FormatException(a.unit, b.unit);
}
const PhysicalNumber ariel::operator-(const ariel::PhysicalNumber & physical)
{
	return PhysicalNumber(-physical.value,physical.unit);
}
const PhysicalNumber & ariel::operator-=(ariel::PhysicalNumber & a, const ariel::PhysicalNumber & b)
{
	if ((a.unit / 3 == b.unit / 3)) {
		long double num = (a.value * ariel::Enumber[a.unit] - b.value * ariel::Enumber[b.unit])/ariel::Enumber[a.unit];
		a.value = num;
		return a;
	}
	else throw FormatException(a.unit, b.unit);
}
const PhysicalNumber & ariel::operator--(ariel::PhysicalNumber & physical)
{
	--physical.value;
	return physical;
}
const PhysicalNumber & ariel::operator--(ariel::PhysicalNumber & physical, int flag)
{
	physical.value--;
	return physical;
}
const PhysicalNumber & ariel::operator++(ariel::PhysicalNumber & physical)
{
	++physical.value;
	return physical;
}
const PhysicalNumber & ariel::operator++(ariel::PhysicalNumber & physical, int flag)
{
	physical.value++;
	return physical;
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
bool ariel::operator!=(const PhysicalNumber& a, const PhysicalNumber& b) {
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
static ariel::Unit getByName(const char* name) {
	ariel::Unit unit;
	return unit;
}
static ariel::Unit get_Enum(std::string name) {
	ariel::Unit unit;
	std::cout << "length: " << ariel::Ename.size() << std::endl;
	for (size_t i = 0; i < ariel::Ename.size(); i++)
	{
		if (name.compare(ariel::Ename[i]) == 0) {
			unit = ariel::Unit(i);
			return unit;
		}
	}
	throw FormatException(name);
}
std::istream & ariel::operator>>(std::istream & is, ariel::PhysicalNumber & physical)
{
	/*long double n_value = 0;
	std::string n_unit;
	is >> n_value >> n_unit;
	physical.value = n_value;
	physical.unit = get_Enum(n_unit);*/
	return is;
}
