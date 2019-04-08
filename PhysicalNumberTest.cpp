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
		
		//tamp
		PhysicalNumber t(0,Unit::MIN);;
		
		//cm,m,km test
		PhysicalNumber cm1 (1,Unit::CM);
		PhysicalNumber m1 (1,Unit::M);
		PhysicalNumber km1 (1,Unit::KM);
		
		PhysicalNumber cm100 (100,Unit::CM);
		PhysicalNumber m1000 (1000,Unit::M);
		
		PhysicalNumber cm101 (101,Unit::CM);
		PhysicalNumber m1001 (1001,Unit::M);
		
	
		

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
			
			
	
			//cm,m,km test - operators >> and <<
			.setname("cm,m,km test - operators >> and <<")
			
			.CHECK_OUTPUT(  cm1 << " " << m1 << " " << km1  ,"1[cm] 1[m] 1[km]" )
			
			.CHECK_OK(istringstream("1[cm]") >> t)
			.CHECK_OUTPUT(t,"1[cm]")
			.CHECK_OK(istringstream("1[m]") >> t)
			.CHECK_OUTPUT(t,"1[m]")
			.CHECK_OK(istringstream("1[km]") >> t)
			.CHECK_OUTPUT(t,"1[km]")
			
			
			//cm,m,km test - operator compare
			.setname("cm,m,km test-operator compare")
			.CHECK_EQUAL((m1 == cm100), true)
			.CHECK_EQUAL((km1 == m1000), true)
			.CHECK_EQUAL((m1 != cm101), true)
			.CHECK_EQUAL((km1 != m1001), true)
			
			.CHECK_EQUAL((km1 > m1), true)
			.CHECK_EQUAL((m1 > cm1), true)
			.CHECK_EQUAL((km1 > cm1), true)
			.CHECK_EQUAL((cm1 < m1), true)
			.CHECK_EQUAL((m1 < km1), true)
			.CHECK_EQUAL((cm1 < km1), true)
			
			.CHECK_EQUAL((m1 <= cm100), true)
			.CHECK_EQUAL((km1 <= m1000), true)
			.CHECK_EQUAL((m1 >= cm100), true)
			.CHECK_EQUAL((km1 >= m1000), true)
			
			.CHECK_EQUAL((km1 >= m1), true)
			.CHECK_EQUAL((m1 >= cm1), true)
			.CHECK_EQUAL((km1 >= cm1), true)
			.CHECK_EQUAL((cm1 <= m1), true)
			.CHECK_EQUAL((m1 <= km1), true)
			.CHECK_EQUAL((cm1 <= km1), true)
			
			
			
			
			//cm,m,km test -Arithmetic operators
			//note: operator+= and operator-= change the valuse
			.setname("cm,m,km test-Arithmetic operators")
			.CHECK_OUTPUT(cm1 + m1,"101[cm]")
			.CHECK_OUTPUT(m1 + cm1,"1.01[m]")
			.CHECK_OUTPUT(m1 + km1,"1001[m]")
			.CHECK_OUTPUT(km1 + m1,"1.001[km]")
			
			.CHECK_OUTPUT(m1 - cm1,"0.99[m]")
			.CHECK_OUTPUT(km1 - m1,"0.999[km]")
			
			.CHECK_OUTPUT(cm101 - m1,"1[cm]")
			.CHECK_OUTPUT(m1001 - km1,"1[m]")
			
			.CHECK_OUTPUT(+cm1,"1[cm]")
			.CHECK_OUTPUT(+m1,"1[m]")
			.CHECK_OUTPUT(+km1,"1[km]")
			.CHECK_OUTPUT(-cm1,"-1[cm]")
			.CHECK_OUTPUT(-m1,"-1[m]")
			.CHECK_OUTPUT(-km1,"-1[km]")
			
			.CHECK_OUTPUT((cm101 -= cm1),"100[cm]")//cm101 = 100 cm
			.CHECK_OUTPUT((m1001 -= m1),"1000[m]")//m1001 = 1000 m
			.CHECK_OUTPUT((m1 += cm101),"2[m]")
			.CHECK_OUTPUT((km1 += m1001),"2[km]")
			
			//cm,m,km test - prefix/postfix operators
			.setname("cm,m,km test-prefix/postfix operators")
			.CHECK_OUTPUT((cm1++),"2[cm]")
			.CHECK_OUTPUT((++cm1),"3[cm]")
			.CHECK_OUTPUT((cm1--),"2[cm]")
			.CHECK_OUTPUT((--cm1),"1[cm]")
			
			.CHECK_OUTPUT((m1++),"3[m]")
			.CHECK_OUTPUT((++m1),"4[m]")
			.CHECK_OUTPUT((m1--),"3[m]")
			.CHECK_OUTPUT((--m1),"2[m]")
			
			.CHECK_OUTPUT((km1++),"3[km]")
			.CHECK_OUTPUT((++km1),"4[km]")
			.CHECK_OUTPUT((km1--),"3[km]")
			.CHECK_OUTPUT((--km1),"2[km]")
			
			
			//Input/output Check
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
			
			//arithmetic Check
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
			
			//Boolean check
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
			
			//Exceptions
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
			/*.CHECK_THROWS((a != b)) expression not build yet
			.CHECK_THROWS((a == b))
			.CHECK_THROWS((a > b))
			.CHECK_THROWS((a >= b))
			.CHECK_THROWS((a < b))
			.CHECK_THROWS((a <= b))*/
			
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