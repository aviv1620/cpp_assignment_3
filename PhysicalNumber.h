#pragma once
#include <iostream>
#include "Unit.h"
namespace ariel {
	class PhysicalNumber {
	private:
		long double value;
		Unit unit;
		

	public:
		PhysicalNumber(long double value, Unit unit);
		int get_number() {
			return value;
		}
		Unit get_unit() {
			return unit;
		}
		friend const PhysicalNumber operator+ (const PhysicalNumber& physical);//+physical
		friend const PhysicalNumber& operator+= (PhysicalNumber& a, const PhysicalNumber& b);//a+=b
		friend const PhysicalNumber operator- (const PhysicalNumber& physical);//-physical
		friend const PhysicalNumber& operator-=(PhysicalNumber& a, const PhysicalNumber& b);//a-=b
		friend const PhysicalNumber& operator--(PhysicalNumber& physical);//prefix
		friend const PhysicalNumber& operator--(PhysicalNumber& physical, int flag);//postfix
		friend const PhysicalNumber& operator++(PhysicalNumber& physical);//prefix
		friend const PhysicalNumber& operator++(PhysicalNumber& physical, int flag);//postfix
		friend const PhysicalNumber operator+ (const PhysicalNumber& a, const PhysicalNumber& b);//a+b
		friend const PhysicalNumber operator-(const PhysicalNumber& a, const PhysicalNumber& b);//a-b

		friend std::ostream& operator<< (std::ostream& os, const PhysicalNumber& physical);
		friend std::istream& operator>> (std::istream& is, PhysicalNumber& physical);

		friend bool operator== (const PhysicalNumber& a, const PhysicalNumber& b);
		friend bool operator!= (const PhysicalNumber& a, const PhysicalNumber& b);
		friend bool operator< (const PhysicalNumber& a, const PhysicalNumber& b);
		friend bool operator<= (const PhysicalNumber& a, const PhysicalNumber& b);
		friend bool operator> (const PhysicalNumber& a, const PhysicalNumber& b);
		friend bool operator>= (const PhysicalNumber& a, const PhysicalNumber& b);
	};
};