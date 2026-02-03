#include "resistor.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <catch2/catch_test_macros.hpp>


using std::ostringstream, std::string, std::to_string, std::vector;

using electronics::Resistor;
using electronics::Unit;


struct ResistorTest;
std::ostream& operator<<(std::ostream& os, const ResistorTest& rt);

struct ResistorTest {
  uint64_t value;
  Unit unit;
  uint64_t expected;
  Unit out_unit{Unit::microohm};
  operator std::string() {
    ostringstream oss;
    oss << *this;
    return oss.str();
  }
};

std::ostream& operator<<(std::ostream& os, const Unit u) {
  switch (u) {
  case Unit::microohm:
    os << " microohm"; break;
  case Unit::milliohm:
    os << " milliohm"; break;
  case Unit::ohm:
    os << " ohm"; break;
  case Unit::kiloohm:
    os << " kiloohm"; break;
  case Unit::megaohm:
    os << " megaohm"; break;
  case Unit::gigaohm:
    os << " gigaohm"; break;
  case Unit::teraohm:
    os << " teraohm"; break;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const ResistorTest& rt) {
  os << rt.value << rt.unit << " -> " << rt.expected << rt.out_unit;
  return os;
}

const vector<ResistorTest> ctor_cases = {
  {       0, Unit::ohm,                        0 },
  {      24, Unit::ohm,                 24000000 },
  {      25, Unit::ohm,                 25000000 },
  {     100, Unit::ohm,                100000000 },
  {     330, Unit::ohm,                330000000 },
  {    3000, Unit::ohm,               3000000000 },
  { 9500000, Unit::ohm,            9500000000000 },
  {       0, Unit::microohm,                   0 },
  {     330, Unit::microohm,                 330 },
  { 9500000, Unit::microohm,             9500000 },
  {       0, Unit::milliohm,                   0 },
  {     330, Unit::milliohm,              330000 },
  { 9500000, Unit::milliohm,          9500000000 },
  {       0, Unit::kiloohm,                    0 },
  {       3, Unit::kiloohm,           3000000000 },
  {       0, Unit::megaohm,                    0 },
  {       1, Unit::megaohm,        1000000000000 },
  {      12, Unit::megaohm,       12000000000000 },
  {       0, Unit::gigaohm,                    0 },
  {       1, Unit::gigaohm,     1000000000000000 },
  {       2, Unit::gigaohm,     2000000000000000 },
  {       0, Unit::teraohm,                    0 },
  {       1, Unit::teraohm,  1000000000000000000 },
  {       2, Unit::teraohm,  2000000000000000000 },
};

const vector<ResistorTest> by_unit_cases = {
  {       0, Unit::ohm,         0, Unit::ohm },
  {      24, Unit::ohm,        24, Unit::ohm },
  {      25, Unit::ohm,        25, Unit::ohm },
  {     100, Unit::ohm,       100, Unit::ohm },
  {     330, Unit::ohm,       330, Unit::ohm },
  {    3000, Unit::ohm,         3, Unit::kiloohm },
  { 9500000, Unit::ohm,      9500, Unit::kiloohm },
  {       0, Unit::microohm,    0, Unit::ohm },
  { 9500000, Unit::milliohm, 9500, Unit::ohm },
  {       0, Unit::kiloohm,     0, Unit::ohm },
  {       3, Unit::kiloohm,     3, Unit::kiloohm },
  {       0, Unit::megaohm,     0, Unit::ohm },
  {       1, Unit::megaohm,  1000, Unit::kiloohm },
  {      12, Unit::megaohm,    12, Unit::megaohm },
  {       0, Unit::gigaohm,     0, Unit::ohm },
  {       1, Unit::gigaohm,  1000, Unit::megaohm },
  {       2, Unit::gigaohm,     2, Unit::gigaohm },
  {       0, Unit::teraohm,     0, Unit::ohm },
  {       1, Unit::teraohm,  1000, Unit::gigaohm },
  {       2, Unit::teraohm,     2, Unit::teraohm },
};


struct CircuitTest {
  uint64_t lhs_value;
  Unit lhs_unit;
  uint64_t rhs_value;
  Unit rhs_unit;
  uint64_t expected;
  Unit out_unit{Unit::microohm};
  operator std::string() {
    ostringstream oss;
    oss << lhs_value << lhs_unit;
    oss << " combined with " << rhs_value << rhs_unit;
    oss << " yields " << expected << out_unit;
    return oss.str();
  }
};

const vector<CircuitTest> series_cases = {
  {       0, Unit::ohm,         0, Unit::ohm,         0, Unit::ohm },
  {      24, Unit::ohm,        24, Unit::ohm,        48, Unit::ohm },
  {      25, Unit::ohm,        25, Unit::kiloohm, 25025, Unit::ohm },
  {     100, Unit::kiloohm,   100, Unit::ohm,    100100, Unit::ohm },
  {     330, Unit::ohm,       330, Unit::ohm,       660, Unit::ohm },
  {    3000, Unit::ohm,         3, Unit::kiloohm,     6, Unit::kiloohm },
  { 9500000, Unit::ohm,      9500, Unit::kiloohm,    19, Unit::megaohm },
  {       0, Unit::microohm,    0, Unit::ohm,         0, Unit::microohm },
  { 9500000, Unit::milliohm, 9500, Unit::ohm,        19, Unit::kiloohm },
  {       0, Unit::kiloohm,     0, Unit::ohm,         0, Unit::kiloohm },
  {       3, Unit::kiloohm,     3, Unit::kiloohm,     6, Unit::kiloohm },
  {       0, Unit::megaohm,     0, Unit::ohm,         0, Unit::megaohm },
  {       1, Unit::megaohm,  1000, Unit::kiloohm,     2, Unit::megaohm },
  {      12, Unit::megaohm,    12, Unit::megaohm,    24, Unit::megaohm },
  {       0, Unit::gigaohm,     0, Unit::ohm,         0, Unit::microohm },
  {       1, Unit::gigaohm,  1000, Unit::megaohm,     2, Unit::gigaohm },
  {       2, Unit::gigaohm,     2, Unit::gigaohm,     4, Unit::gigaohm },
  {       0, Unit::teraohm,     0, Unit::ohm,         0, Unit::milliohm },
  {       1, Unit::teraohm,  1000, Unit::gigaohm,     2, Unit::teraohm },
  {       2, Unit::teraohm,     2, Unit::teraohm,     4, Unit::teraohm },
};

const vector<CircuitTest> parallel_cases = {
  {      24, Unit::ohm,         0, Unit::ohm,         0, Unit::ohm },
  {       0, Unit::ohm,        25, Unit::kiloohm,     0, Unit::ohm },
  {     100, Unit::ohm,       100, Unit::ohm,        50, Unit::ohm },
  {     330, Unit::ohm,       330, Unit::ohm,       165, Unit::ohm },
  {    3000, Unit::ohm,         3, Unit::kiloohm,  1500, Unit::ohm },
  { 9500000, Unit::ohm,      9500, Unit::kiloohm,  4750, Unit::kiloohm },
  { 9500000, Unit::milliohm, 9500, Unit::ohm,      4750, Unit::ohm },
  {       3, Unit::kiloohm,     3, Unit::kiloohm,  1500, Unit::ohm },
  {       1, Unit::megaohm,  1000, Unit::kiloohm,   500, Unit::kiloohm },
  {      12, Unit::megaohm,    12, Unit::megaohm,     6, Unit::megaohm },
  {       1, Unit::gigaohm,  1000, Unit::megaohm,   500, Unit::megaohm },
  {       2, Unit::gigaohm,     2, Unit::gigaohm,     1, Unit::gigaohm },
  {       1, Unit::teraohm,  1000, Unit::gigaohm,   500, Unit::gigaohm },
  {       2, Unit::teraohm,     2, Unit::teraohm,     1, Unit::teraohm },
  {     400, Unit::ohm,       100, Unit::ohm,        80, Unit::ohm },
  {     900, Unit::ohm,       600, Unit::ohm,       360, Unit::ohm },
};


TEST_CASE("default_constructor") {
  Resistor r;
  REQUIRE(330'000'000 == r.resistance());
}


TEST_CASE("constructor") {
  for (ResistorTest t : ctor_cases) {
    const Resistor actual(t.value, t.unit);
    INFO(static_cast<string>(t));
    REQUIRE(t.expected == actual.resistance());
  }
}


TEST_CASE("resistance_by_unit") {
  for (ResistorTest t : by_unit_cases) {
    const Resistor actual(t.value, t.unit);
    INFO(static_cast<string>(t));
    REQUIRE(t.expected == actual.resistance(t.out_unit));
  }
}


TEST_CASE("op_plus") {
  for (CircuitTest t : series_cases) {
    const Resistor lhs{t.lhs_value, t.lhs_unit};
    const Resistor rhs{t.rhs_value, t.rhs_unit};
    const Resistor actual{lhs + rhs};

    INFO(static_cast<string>(t));
    CHECK(t.expected == actual.resistance(t.out_unit));
  }
}


TEST_CASE("op_pipe") {
  for (CircuitTest t : parallel_cases) {
    const Resistor lhs{t.lhs_value, t.lhs_unit};
    const Resistor rhs{t.rhs_value, t.rhs_unit};
    const Resistor actual{lhs | rhs};

    INFO(static_cast<string>(t));
    CHECK(t.expected == actual.resistance(t.out_unit));
  }
}


TEST_CASE("op_equal") {
  for (ResistorTest t : by_unit_cases) {
    const Resistor lhs{t.value, t.unit};
    const Resistor rhs{t.expected, t.out_unit};
    INFO(static_cast<string>(t));
    CHECK(lhs == rhs);
  }
  REQUIRE(Resistor {0, Unit::ohm} != Resistor {1, Unit::ohm});
}
