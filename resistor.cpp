#include"resistor.hpp"
#include<math.h>
#include<cstdint>
namespace electronics{
  uint64_t Resistor::resistance(Unit unit)const{

    uint64_t value;
    uint64_t value2;
    switch(unit){
      case Unit::microohm:
        value=1;
        break;
      case Unit::milliohm:
        value =1000;
        break;
      case Unit::ohm:
        value =1000000;
        break;
      case Unit::kiloohm:
        value =1000000000;
        break;
      case Unit::megaohm:
        value = 1000000000000;
        break;
      case Unit::gigaohm:
        value = 1000000000000000;
        break;
      case Unit::teraohm:
        value =1000000000000000000;
        break;

    }

    switch(unit_){
      case Unit::microohm:
        value2=1;
        break;
      case Unit::milliohm:
        value2 =1000;
        break;
      case Unit::ohm:
        value2 =1000000;
        break;
      case Unit::kiloohm:
        value2 =1000000000;
        break;
      case Unit::megaohm:
        value2 = 1000000000000;
        break;
      case Unit::gigaohm:
        value2 = 1000000000000000;
        break;
      case Unit::teraohm:
        value2 =1000000000000000000;
        break;

    }

    double value3 = value/value2;
    return static_cast<int64_t>(wert_*value3);
  };

  Resistor Resistor::operator+(const Resistor& other)const{
    uint64_t value = resistance()+other.resistance();
    return Resistor{value,Unit::microohm};
  };

  Resistor Resistor::operator|(const Resistor& other)const{
    uint64_t value = static_cast<uint64_t>(static_cast<double>(resistance()*other.resistance())/(resistance()+other.resistance()));
    return Resistor{value,Unit::microohm};
  };
}
