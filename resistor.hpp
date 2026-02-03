#ifndef RESISTOR_HPP
#define RESISTOR_HPP

#include<math.h>
#include<cstdint>

namespace electronics{

  enum class Unit{
    microohm,
    milliohm,
    ohm,
    kiloohm,
    megaohm,
    gigaohm,
    teraohm
  };

  class Resistor {
    public:
      Resistor():wert_{330},unit_{Unit::ohm}{};
      Resistor(uint64_t value, Unit unit){
        wert_ =value;
        unit_=unit;
      };
      uint64_t resistance()const {
        uint64_t value;
        switch(unit_){
         case Unit::microohm:
          return wert_;
         break;
          case Unit::milliohm:
            value=wert_*1000;
            return value;
            break;
          case Unit::ohm:
            value=wert_*1000000;
            return value;
            break;
          case Unit::kiloohm:
            value=wert_*1000000000;
            return value;
            break;
          case Unit::megaohm:
            value=wert_*1000000000000;
            return value;
            break;
          case Unit::gigaohm:
            value=wert_*1000000000000000;
            return value;
            break;
          case Unit::teraohm:
            value=wert_*1000000000000000000;
            return value;
            break;
      }

      };
      uint64_t resistance(Unit unit)const;
      Resistor operator+(const Resistor& other)const;
      Resistor operator|(const Resistor& other)const;
      bool operator==(const Resistor& other)const{
        return resistance()==other.resistance();
      };
   private:
      uint64_t wert_;
      Unit unit_;
  };
}

#endif
