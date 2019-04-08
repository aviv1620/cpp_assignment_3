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
		
		//SEC, MIN, HOUR test
		PhysicalNumber sec1 (1,Unit::SEC);
		PhysicalNumber min1 (1,Unit::MIN);
		PhysicalNumber hour1 (1,Unit::HOUR);
		
		PhysicalNumber sec60 (60,Unit::SEC);
		PhysicalNumber min60 (60,Unit::MIN);
		
		PhysicalNumber sec61 (61,Unit::SEC);
		PhysicalNumber min61 (61,Unit::MIN);
		
		//G, KG, TON
		PhysicalNumber g1 (1,Unit::G);
		PhysicalNumber kg1 (1,Unit::KG);
		PhysicalNumber ton1 (1,Unit::TON);
		
		PhysicalNumber g1000 (1000,Unit::G);
		PhysicalNumber kg1000 (1000,Unit::KG);
		
		PhysicalNumber g1001 (1001,Unit::G);
		PhysicalNumber kg1001 (1001,Unit::KG);
		

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
			.CHECK_OUTPUT(m1 - km1,"-999[m]")//negetive number.
			
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
			
			//SEC, MIN, HOUR test - operators >> and <<
			.setname("SEC, MIN, HOUR test - operators >> and <<")
			
			.CHECK_OUTPUT(  sec1 << " " << min1 << " " << hour1  ,"1[sec] 1[min] 1[hour]" )
			
			.CHECK_OK(istringstream("1[sec]") >> t)
			.CHECK_OUTPUT(t,"1[sec]")
			.CHECK_OK(istringstream("1[min]") >> t)
			.CHECK_OUTPUT(t,"1[min]")
			.CHECK_OK(istringstream("1[hour]") >> t)
			.CHECK_OUTPUT(t,"1[hour]")
			
			
			//SEC, MIN, HOUR test - operator compare
			.setname("SEC, MIN, HOUR test-operator compare")
			.CHECK_EQUAL((min1 == sec60), true)
			.CHECK_EQUAL((hour1 == min60), true)
			.CHECK_EQUAL((min1 != sec61), true)
			.CHECK_EQUAL((hour1 != min61), true)
			
			.CHECK_EQUAL((hour1 > min1), true)
			.CHECK_EQUAL((min1 > sec1), true)
			.CHECK_EQUAL((hour1 > sec1), true)
			.CHECK_EQUAL((min1 < hour1), true)
			.CHECK_EQUAL((sec1 < min1), true)
			.CHECK_EQUAL((sec1 < hour1), true)
			
			.CHECK_EQUAL((min1 <= sec60), true)
			.CHECK_EQUAL((hour1 <= min60), true)
			.CHECK_EQUAL((min1 >= sec60), true)
			.CHECK_EQUAL((hour1 >= min60), true)
			
			.CHECK_EQUAL((hour1 >= min1), true)
			.CHECK_EQUAL((min1 >= sec1), true)
			.CHECK_EQUAL((hour1 >= sec1), true)
			.CHECK_EQUAL((min1 <= hour1), true)
			.CHECK_EQUAL((sec1 <= min1), true)
			.CHECK_EQUAL((sec1 <= hour1), true)
			
			//SEC, MIN, HOUR test -Arithmetic operators
			//note: operator+= and operator-= change the valuse
			.setname("SEC, MIN, HOUR test-Arithmetic operators")
			.CHECK_OUTPUT(sec1 + min1,"61[sec]")
			.CHECK_OUTPUT(min1 + hour1,"61[min]")
			.CHECK_OUTPUT(min1 + sec1 - sec1,"1[min]")
			.CHECK_OUTPUT(hour1 + sec1 - sec1,"1[hour]")
			
			.CHECK_OUTPUT(sec1 - min1,"-59[sec]")//negetive number.
			
			.CHECK_OUTPUT(sec61 - sec1,"60[sec]")
			.CHECK_OUTPUT(min61 - min1,"60[min]")
			
			.CHECK_OUTPUT(+sec1,"1[sec]")
			.CHECK_OUTPUT(+min1,"1[min]")
			.CHECK_OUTPUT(+hour1,"1[hour]")
			.CHECK_OUTPUT(-sec1,"-1[sec]")
			.CHECK_OUTPUT(-min1,"-1[min]")
			.CHECK_OUTPUT(-hour1,"-1[hour]")
			
			.CHECK_OUTPUT((sec61 -= sec1),"60[sec]")//cm101 = 100 cm
			.CHECK_OUTPUT((min61 -= min1),"60[min]")//m1001 = 1000 m
			.CHECK_OUTPUT((min1 += sec60),"2[min]")
			.CHECK_OUTPUT((hour1 += min60),"2[hour]")
			
			//SEC, MIN, HOUR test - prefix/postfix operators
			.setname("SEC, MIN, HOUR test-prefix/postfix operators")
			.CHECK_OUTPUT((sec1++),"2[sec]")
			.CHECK_OUTPUT((++sec1),"3[sec]")
			.CHECK_OUTPUT((sec1--),"2[sec]")
			.CHECK_OUTPUT((--sec1),"1[sec]")
			
			.CHECK_OUTPUT((min1++),"3[min]")
			.CHECK_OUTPUT((++min1),"4[min]")
			.CHECK_OUTPUT((min1--),"3[min]")
			.CHECK_OUTPUT((--min1),"2[min]")
			
			.CHECK_OUTPUT((hour1++),"3[hour]")
			.CHECK_OUTPUT((++hour1),"4[hour]")
			.CHECK_OUTPUT((hour1--),"3[hour]")
			.CHECK_OUTPUT((--hour1),"2[hour]")
			
			//G, KG, TON test - operators >> and <<
			.setname("G, KG, TON test - operators >> and <<")
			
			.CHECK_OUTPUT(  g1 << " " << kg1 << " " << ton1  ,"1[g] 1[kg] 1[ton]" )
			
			.CHECK_OK(istringstream("1[g]") >> t)
			.CHECK_OUTPUT(t,"1[g]")
			.CHECK_OK(istringstream("1[kg]") >> t)
			.CHECK_OUTPUT(t,"1[kg]")
			.CHECK_OK(istringstream("1[ton]") >> t)
			.CHECK_OUTPUT(t,"1[ton]")
			
			
			//G, KG, TON test - operator compare
			.setname("G, KG, TON test-operator compare")
			.CHECK_EQUAL((kg1 == g1000), true)
			.CHECK_EQUAL((ton1 == kg1000), true)
			.CHECK_EQUAL((kg1 != g1001), true)
			.CHECK_EQUAL((ton1 != kg1001), true)
			
			.CHECK_EQUAL((ton1 > kg1), true)
			.CHECK_EQUAL((kg1 > g1), true)
			.CHECK_EQUAL((ton1 > g1), true)
			.CHECK_EQUAL((kg1 < ton1), true)
			.CHECK_EQUAL((g1 < kg1), true)
			.CHECK_EQUAL((g1 < ton1), true)
			
			.CHECK_EQUAL((ton1 <= kg1000), true)
			.CHECK_EQUAL((kg1 <= g1000), true)
			.CHECK_EQUAL((ton1 >= kg1000), true)
			.CHECK_EQUAL((kg1 >= g1000), true)
			
			.CHECK_EQUAL((ton1 >= kg1), true)
			.CHECK_EQUAL((kg1 >= g1), true)
			.CHECK_EQUAL((ton1 >= g1), true)
			.CHECK_EQUAL((kg1 <= ton1), true)
			.CHECK_EQUAL((g1 <= kg1), true)
			.CHECK_EQUAL((g1 <= ton1), true)
			
			
			
			
			//G, KG, TON test -Arithmetic operators
			//note: operator+= and operator-= change the valuse
			.setname("G, KG, TON test-Arithmetic operators")
			.CHECK_OUTPUT(g1 + kg1,"1001[g]")
			.CHECK_OUTPUT(kg1 + g1,"1.001[kg]")
			.CHECK_OUTPUT(kg1 + ton1,"1001[kg]")
			.CHECK_OUTPUT(ton1 + kg1,"1.001[ton]")
			
			.CHECK_OUTPUT(kg1 - g1,"0.999[kg]")
			.CHECK_OUTPUT(ton1 - kg1,"0.999[ton]")
			.CHECK_OUTPUT(kg1 - ton1,"-999[kg]")//negetive number.
			
			.CHECK_OUTPUT(g1001 - kg1,"1[g]")
			.CHECK_OUTPUT(kg1001 - ton1,"1[kg]")
			
			.CHECK_OUTPUT(+g1,"1[g]")
			.CHECK_OUTPUT(+kg1,"1[kg]")
			.CHECK_OUTPUT(+ton1,"1[ton]")
			.CHECK_OUTPUT(-g1,"-1[g]")
			.CHECK_OUTPUT(-kg1,"-1[kg]")
			.CHECK_OUTPUT(-ton1,"-1[ton]")

			
			.CHECK_OUTPUT((g1001 -= g1),"1000[g]")//g1001 = 1000 g
			.CHECK_OUTPUT((kg1001 -= kg1),"1000[kg]")
			.CHECK_OUTPUT((kg1 += g1001),"2[kg]")
			.CHECK_OUTPUT((ton1 += kg1001),"2[ton]")
			
			//G, KG, TON test - prefix/postfix operators
			.setname("G, KG, TON test-prefix/postfix operators")
			.CHECK_OUTPUT((g1++),"2[g]")
			.CHECK_OUTPUT((++g1),"3[g]")
			.CHECK_OUTPUT((g1--),"2[g]")
			.CHECK_OUTPUT((--g1),"1[g]")
			
			.CHECK_OUTPUT((kg1++),"3[kg]")
			.CHECK_OUTPUT((++kg1),"4[kg]")
			.CHECK_OUTPUT((kg1--),"3[kg]")
			.CHECK_OUTPUT((--kg1),"2[kg]")
			
			.CHECK_OUTPUT((ton1++),"3[ton]")
			.CHECK_OUTPUT((++ton1),"4[ton]")
			.CHECK_OUTPUT((ton1--),"3[ton]")
			.CHECK_OUTPUT((--ton1),"2[ton]")
									
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