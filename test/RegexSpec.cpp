#include <catch2/catch.hpp>

#include "regex/Regex.h"
using Regex::Chars;
using Regex::Concatenate;
using Regex::EmptyString;
using Regex::KleeneStar;
using Regex::Union;

SCENARIO("Representing Regex as a string") {
  GIVEN("A Chars regex with some chars") {
    Chars re{'a', 'b', 'c'};
    WHEN("The regex is coverted to a string") {
      auto s = re.toString();
      THEN("It will have the same representation as a CharSet") {
        REQUIRE(s == Regex::CharSet{'a', 'b', 'c'}.toString());
      }
    }
  }
  GIVEN("An empty Chars") {
    Chars re;
    WHEN("The regex is converted to a string") {
      auto s = re.toString();
      THEN("The string will be the symbol for nullset") { REQUIRE(s == "Ø"); }
    }
  }

  GIVEN("A Concatenation regex") {
    Chars a{'a'};
    Chars b{'b'};
    Concatenate re(a, b);
    WHEN("The concat retgex is converted to a string") {
      auto s = re.toString();
      THEN("The string will be the concatenation of the a and b Chars") {
        REQUIRE(s == "{a} ~ {b}");
      }
    }
  }
}
