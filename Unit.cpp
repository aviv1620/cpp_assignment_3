#include <iostream>
#include "Unit.h"
//Distance Units
int operator"" _km(const unsigned long long km) {
	return km * 100000;
}
int operator"" _m(const unsigned long long m) {
	return m * 100;
}
int operator"" _cm(const unsigned long long cm) {
	return cm * 1;
}
//Mass Units
int operator"" _ton(const unsigned long long ton) {
	return ton * 1000000;
}
int operator"" _kg(const unsigned long long kg) {
	return kg * 1000;
}
int operator"" _g(const unsigned long long g) {
	return g * 1;
}
//Time Units
int operator"" _hour(const unsigned long long hour) {
	return hour * 3600;
}
int operator"" _min(const unsigned long long min) {
	return min * 60;
}
int operator"" _sec(const unsigned long long sec) {
	return sec * 1;
}