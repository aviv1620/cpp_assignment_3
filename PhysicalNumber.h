#include "Unit.h"


namespace ariel{
	using std::ostream;
	
	class PhysicalNumber{
		private:
			int value;
			Unit unit;
			
		public:
			PhysicalNumber(int v,Unit u){
			}
			
		friend ostream& operator<< (ostream& os, const PhysicalNumber& pn){
			return (os << "test");
		}
		
		const PhysicalNumber operator+(const PhysicalNumber& other) const {
			return PhysicalNumber(666,Unit::KM);
		}
		
		const PhysicalNumber operator-(const PhysicalNumber& other) const {
			return PhysicalNumber(666,Unit::KM);
		}
		
		// prefix increment:
		PhysicalNumber& operator-() {
			return *this;
		}
    
	
	};
}