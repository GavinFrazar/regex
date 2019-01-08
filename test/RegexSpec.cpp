#include <catch2/catch.hpp>

#include "regex/Regex.h"
using Regex::Chars;
using Regex::Concatenate;
using Regex::EmptyString;
using Regex::KleeneStar;
using Regex::Union;

SCENARIO("Representing Regex as a string") {
  Chars a{'a'};
  Chars b{'b'};
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
      THEN("The string will be the symbol for nullset") { REQUIRE(s == "∅"); }
    }
  }
  GIVEN("A Concatenation of Char regex") {
    Concatenate re(a, b);
    WHEN("The concat regex is converted to a string") {
      auto s = re.toString();
      THEN("The string will be the concatenation of the a and b Chars") {
        REQUIRE(s == "({a} ~ {b})");
      }
    }
  }
  GIVEN("A Union of Char regex"){
    Union re(a,b);
    WHEN("The union regex is converted to a string"){
      auto s = re.toString();
      THEN("The string will be the union of the a and b Chars"){
        REQUIRE(s == "({a} | {b})");
      }
    }
  }
  GIVEN("A KleeneStar of a Char"){
    KleeneStar re(a);
    WHEN("The KleeneStar regex is converted to a string"){
      auto s = re.toString();
      THEN("The string will be the kleenestar of the a Char"){
        REQUIRE(s == "({a})*");
      }
    }
  }
  GIVEN("The empty string regex"){
    EmptyString re;
    WHEN("The empty string regex is converted to a string"){
      auto s = re.toString();
      THEN("The string will be epsilon"){
        REQUIRE(s == "ε");
      }
    }
  }
}
