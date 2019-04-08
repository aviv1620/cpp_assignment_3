#pragma once
#include <iostream>
#include <string>
#include <vector>
namespace ariel {
		enum Unit {
			M, KM, CM,
			SEC, MIN, HOUR,
			G, KG, TON
		};
		static const std::vector<std::string> Ename{ "[m]","[km]","[cm]","[sec]","[min]","[hour]","[g]","[kg]","[ton]" };
		static const std::vector<long int> Enumber = { 100,100000,1,1,60,3600,1,1000,1000000 };
};