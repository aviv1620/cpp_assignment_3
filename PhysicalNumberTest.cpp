/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main() {
	badkan::TestCase testcase;
	int grade = 0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0) {

		// BASIC TESTS - DO NOT CHANGE
		PhysicalNumber a(2, Unit::KM);
		PhysicalNumber b(300, Unit::M);
		PhysicalNumber c(2, Unit::HOUR);
		PhysicalNumber d(30, Unit::MIN);

		testcase
			.setname("Basic output")
			.CHECK_OUTPUT(a, "2[km]")
			.CHECK_OUTPUT(b, "300[m]")

			.setname("Compatible dimensions")
			.CHECK_OUTPUT(b + a, "2300[m]")
			.CHECK_OUTPUT((a += b), "2.3[km]")
			.CHECK_OUTPUT(a, "2.3[km]")
			.CHECK_OUTPUT(a + a, "4.6[km]")
			.CHECK_OUTPUT(b - b, "0[m]")
			.CHECK_OUTPUT(c, "2[hour]")
			.CHECK_OUTPUT(d, "30[min]")
			.CHECK_OUTPUT(d + c, "150[min]")

			.setname("Incompatible dimensions")
			.CHECK_THROWS(a + c)
			.CHECK_THROWS(a + d)
			.CHECK_THROWS(b + c)
			.CHECK_THROWS(b + d)

			.setname("Basic input")
			.CHECK_OK(istringstream("700[kg]") >> a)
			.CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")

			// YOUR TESTS - INSERT AS MANY AS YOU WANT
			.setname("My tests")

			.setname("Input/output Check")
			.CHECK_OK(istringstream("1000[m]") >> a)
			.CHECK_OUTPUT(a, "1000[m]")
			.CHECK_OK(istringstream("1000[km]") >> a)
			.CHECK_OUTPUT(a, "1000[km]")
			.CHECK_OK(istringstream("1000[cm]") >> a)
			.CHECK_OUTPUT(a, "1000[cm]")
			.CHECK_OK(istringstream("1000[sec]") >> a)
			.CHECK_OUTPUT(a, "1000[sec]")
			.CHECK_OK(istringstream("1000[min]") >> a)
			.CHECK_OUTPUT(a, "1000[min]")
			.CHECK_OK(istringstream("1000[hour]") >> a)
			.CHECK_OUTPUT(a, "1000[hour]")
			.CHECK_OK(istringstream("1000[g]") >> a)
			.CHECK_OUTPUT(a, "1000[g]")
			.CHECK_OK(istringstream("1000[kg]") >> a)
			.CHECK_OUTPUT(a, "1000[kg]")
			.CHECK_OK(istringstream("1000[ton]") >> a)
			.CHECK_OUTPUT(a, "1000[ton]")
			.CHECK_OK(istringstream("1000.12[m]") >> a)
			.CHECK_OUTPUT(a, "1000.12[m]")
			.CHECK_OK(istringstream("1000.12[km]") >> a)
			.CHECK_OUTPUT(a, "1000.12[km]")
			.CHECK_OK(istringstream("1000.12[cm]") >> a)
			.CHECK_OUTPUT(a, "1000.12[cm]")
			.CHECK_OK(istringstream("1000.12[sec]") >> a)
			.CHECK_OUTPUT(a, "1000.12[sec]")
			.CHECK_OK(istringstream("1000.12[min]") >> a)
			.CHECK_OUTPUT(a, "1000.12[min]")
			.CHECK_OK(istringstream("1000.12[hour]") >> a)
			.CHECK_OUTPUT(a, "1000.12[hour]")
			.CHECK_OK(istringstream("1000.12[g]") >> a)
			.CHECK_OUTPUT(a, "1000.12[g]")
			.CHECK_OK(istringstream("1000.12[kg]") >> a)
			.CHECK_OUTPUT(a, "1000.12[kg]")
			.CHECK_OK(istringstream("1000.12[ton]") >> a)
			.CHECK_OUTPUT(a, "1000.12[ton]")
			
			.setname("arithmetic Check")
			.CHECK_OK(istringstream("10[cm]") >> a)
			.CHECK_OK(istringstream("2[m]") >> b)
			.CHECK_OUTPUT((+a),"10[cm]")
			.CHECK_OUTPUT((-a),"-10[cm]")
			.CHECK_OUTPUT((+b),"2[m]")
			.CHECK_OUTPUT((-b),"-2[m]")
			.CHECK_OUTPUT(a + b, "210[cm]")
			.CHECK_OUTPUT(b + a, "2.1[m]")
			.CHECK_OUTPUT(a + a, "20[cm]")
			.CHECK_OUTPUT(b + b, "4[m]")
			.CHECK_OUTPUT(a - b, "-190[cm]")
			.CHECK_OUTPUT(b - a, "1.9[m]")
			.CHECK_OUTPUT(++a, "11[cm]")
			.CHECK_OUTPUT(a + b, "211[cm]")
			.CHECK_OUTPUT(b + a, "2.11[m]")
			.CHECK_OUTPUT(a + a, "22[cm]")
			.CHECK_OUTPUT(a - b, "-189[cm]")
			.CHECK_OUTPUT(b - a, "1.89[m]")
			.CHECK_OUTPUT(--a, "10[cm]")
			.CHECK_OUTPUT(a + b, "210[cm]")
			.CHECK_OUTPUT(b + a, "2.1[m]")
			.CHECK_OUTPUT(a + a, "20[cm]")
			.CHECK_OUTPUT(a - b, "-190[cm]")
			.CHECK_OUTPUT(b - a, "1.9[m]")
			.CHECK_OUTPUT(a++, "11[cm]")
			.CHECK_OUTPUT(a + b, "211[cm]")
			.CHECK_OUTPUT(b + a, "2.11[m]")
			.CHECK_OUTPUT(a + a, "22[cm]")
			.CHECK_OUTPUT(a - b, "-189[cm]")
			.CHECK_OUTPUT(b - a, "1.89[m]")
			.CHECK_OUTPUT(a--, "10[cm]")
			.CHECK_OUTPUT(a + b, "210[cm]")
			.CHECK_OUTPUT(b + a, "2.1[m]")
			.CHECK_OUTPUT(a + a, "20[cm]")
			.CHECK_OUTPUT(a - b, "-190[cm]")
			.CHECK_OUTPUT(b - a, "1.9[m]")
			.CHECK_OUTPUT((a += b),"210[cm]")
			.CHECK_OUTPUT(a,"210[cm]")
			.CHECK_OUTPUT(a + b, "410[cm]")
			.CHECK_OUTPUT(b + a, "4.1[m]")
			.CHECK_OUTPUT(a + a, "420[cm]")
			.CHECK_OUTPUT(a - b, "10[cm]")
			.CHECK_OUTPUT(b - a, "-0.1[m]")
			.CHECK_OUTPUT((a -= b),"10[cm]")
			.CHECK_OUTPUT(a + b, "210[cm]")
			.CHECK_OUTPUT(b + a, "2.1[m]")
			.CHECK_OUTPUT(a + a, "20[cm]")
			.CHECK_OUTPUT(b + b, "4[m]")
			.CHECK_OUTPUT(a - b, "-190[cm]")
			.CHECK_OUTPUT(b - a, "1.9[m]")
			
			.setname("Boolean check")
			.CHECK_OK(istringstream("10[kg]") >> a)
			.CHECK_OK(istringstream("2[kg]") >> b)
			.CHECK_EQUAL( ( a !=b ) ,true)
			.CHECK_EQUAL(( a == b ) , false)
			.CHECK_EQUAL( ( a > b ) ,true)
			.CHECK_EQUAL( ( a >= b ) ,true)
			.CHECK_EQUAL( ( a < b ) ,false)
			.CHECK_EQUAL( ( a <= b ) ,false)
			.CHECK_OK(istringstream("2[kg]") >> a)
			.CHECK_EQUAL((a != b), false)
			.CHECK_EQUAL((a == b), true)
			.CHECK_EQUAL((a > b), false)
			.CHECK_EQUAL((a >= b), true)
			.CHECK_EQUAL((a < b), false)
			.CHECK_EQUAL((a <= b), true)
			.CHECK_OK(istringstream("22[kg]") >> b)
			.CHECK_EQUAL((a != b), true)
			.CHECK_EQUAL((a == b), false)
			.CHECK_EQUAL((a > b), false)
			.CHECK_EQUAL((a >= b), false)
			.CHECK_EQUAL((a < b), true)
			.CHECK_EQUAL((a <= b), true)
			.CHECK_OK(istringstream("10[kg]") >> a)
			.CHECK_OK(istringstream("2000[g]") >> b)
			.CHECK_EQUAL( ( a !=b ) ,true)
			.CHECK_EQUAL(( a == b ) , false)
			.CHECK_EQUAL( ( a > b ) ,true)
			.CHECK_EQUAL( ( a >= b ) ,true)
			.CHECK_EQUAL( ( a < b ) ,false)
			.CHECK_EQUAL( ( a <= b ) ,false)
			.CHECK_OK(istringstream("2[kg]") >> a)
			.CHECK_EQUAL((a != b), false)
			.CHECK_EQUAL((a == b), true)
			.CHECK_EQUAL((a > b), false)
			.CHECK_EQUAL((a >= b), true)
			.CHECK_EQUAL((a < b), false)
			.CHECK_EQUAL((a <= b), true)
			.CHECK_OK(istringstream("22[kg]") >> b)
			.CHECK_EQUAL((a != b), true)
			.CHECK_EQUAL((a == b), false)
			.CHECK_EQUAL((a > b), false)
			.CHECK_EQUAL((a >= b), false)
			.CHECK_EQUAL((a < b), true)
			.CHECK_EQUAL((a <= b), true)
			
			.setname("Exceptions")
			.CHECK_THROWS(istringstream("12")>>a)
			.CHECK_THROWS(istringstream("[km]")>>a)
			.CHECK_THROWS(istringstream("11[k]")>>a)
			.CHECK_THROWS(istringstream("11[km")>>a)
			.CHECK_OK(istringstream("12[sec]") >> a)
			.CHECK_OK(istringstream("2[ton]") >> b)
			.CHECK_THROWS(a + b)
			.CHECK_THROWS(a - b)
			.CHECK_THROWS((a -= b))
			.CHECK_THROWS((a += b))
			.CHECK_THROWS((a != b))
			.CHECK_THROWS((a == b))
			.CHECK_THROWS((a > b))
			.CHECK_THROWS((a >= b))
			.CHECK_THROWS((a < b))
			.CHECK_THROWS((a <= b))
			
			.print(cout, /*show_grade=*/false);
		grade = testcase.grade();
	}
	else {
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "*** Grade: " << grade << " ***" << endl;
	return grade;
}