#include"resistor.hpp"
#include<math.h>
#include<cstdint>
namespace electronics{
  uint64_t Resistor::resistance(Unit unit)const{

    uint64_t value=0;

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

    if(wert_==0){return 0;}else{
    //double value2 = static_cast<double>(resistance())/value;
    return resistance()/value;
    }
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
