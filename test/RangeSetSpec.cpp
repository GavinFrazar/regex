#include <catch2/catch.hpp>

#include "../src/regex/RangeSet.h"
using Regex::CharSet;

SCENARIO("CharSets can determine correctly whether they contain a char") {
  GIVEN("A CharSet with some chars") {
    CharSet cs{'a', 'b', 'c'};
    WHEN("A char inside the CharSet is searched for") {
      bool containsChar = cs.contains('b');
      THEN("The char is found in the CharSet") { REQUIRE(containsChar); }
    }
    WHEN("A char NOT inside the CharSet is searched for") {
      bool doesNotContainChar = !cs.contains('z');
      THEN("The char is not found in the CharSet") {
        REQUIRE(doesNotContainChar);
      }
    }
  }
}

SCENARIO("Taking the union of two CharSets") {
  GIVEN("Two arbitrary CharSet with some overlapping intervals") {
    CharSet A{'a', 'b', 'c'};
    CharSet B{'b', 'd', 'f', 'a'};
    WHEN("CharSets A and B are unioned as CharSet C") {
      CharSet C = A | B;
      THEN("C contains all of A") {
        bool containsA = C.contains('a') && C.contains('b') && C.contains('c');
        REQUIRE(containsA);
      }
      THEN("c contains all of B") {
        bool containsB = C.contains('b') && C.contains('d') &&
                         C.contains('f') && C.contains('f') && C.contains('a');
        REQUIRE(containsB);
      }
    }
  }
}

SCENARIO("Taking the intersection of two CharSets") {
  GIVEN("Two arbitrary CharSet with some overlapping intervals") {
    CharSet A{'a', 'b', 'c'};
    CharSet B{'b', 'd', 'f', 'a'};
    WHEN("CharSets A and B are intersected as CharSet C") {
      CharSet C = A & B;
      THEN("C contains elements in A and B") {
        bool containsAandB = C.contains('a') && C.contains('b');
        REQUIRE(containsAandB);
      }
      THEN("C does NOT contain elements in A which are not in B") {
        bool doesNotContainAnotInB = !C.contains('c');
        REQUIRE(doesNotContainAnotInB);
      }
      THEN("C does NOT contain elements in B which are not in A") {
        bool doesNotContainBnotInA = !(C.contains('d') || C.contains('f'));
        REQUIRE(doesNotContainBnotInA);
      }
    }
  }
}

SCENARIO("Taking the complement of a CharSet") {
  GIVEN("A CharSet with some chars") {
    CharSet cs{'a', 'c', 'e'};
    WHEN("The complement of the CharSet is taken") {
      CharSet comp = !cs;
      THEN("The complement does not contain any char in the original CharSet") {
        REQUIRE_FALSE(comp.contains('a'));
        REQUIRE_FALSE(comp.contains('c'));
        REQUIRE_FALSE(comp.contains('e'));
      }
      THEN("The complement contains every char not in the original CharSet") {
        for (char c = CharSet::minValue; c != 'a'; c += CharSet::one) {
          REQUIRE(comp.contains(c));
        }
        REQUIRE(comp.contains('b'));
        REQUIRE(comp.contains('d'));
        for (char c = CharSet::maxValue; c != 'e'; c -= CharSet::one) {
          REQUIRE(comp.contains(c));
        }
      }
    }
  }
  GIVEN("An empty CharSet") {
    CharSet cs;
    WHEN("The complement of the empty CharSet is taken") {
      CharSet comp = !cs;
      THEN("The complement will be the entire alphabet") {
        for (char c = CharSet::minValue; c <= CharSet::maxValue;
             c += CharSet::one) {
          REQUIRE(comp.contains(c));
        }
      }
    }
  }
}

SCENARIO("Find the minimum char in a CharSet") {
  GIVEN("A CharSet with some chars") {
    CharSet cs{'x', 'z', 'c', 'd', 'b', 'f'};
    WHEN("The minimum element is asked for") {
      std::optional<char> min = cs.minElement();
      THEN("The minimum element in the set is returned") {
        REQUIRE(min);
        REQUIRE(min.value() == 'b');
      }
    }
  }
  GIVEN("An empty CharSet") {
    CharSet cs;
    WHEN("The minimum element is asked for") {
      std::optional<char> min = cs.minElement();
      THEN("The option is none") { REQUIRE(!min); }
    }
  }
}

SCENARIO("Print a CharSet") {
  GIVEN("A CharSet with some chars") {
    using Interval = CharSet::Interval;
    CharSet cs({Interval('a', 'b'), Interval('g', 'x'), Interval('e', 'e')});
    WHEN("The CharSet is converted to a string representation") {
      std::string s = cs.toString();
      THEN("The string will correctly describe the CharSet") {
        REQUIRE(s == "{(a,b), e, (g,x)}");
      }
    }
  }
  GIVEN("A CharSet with a single char") {
    CharSet cs{'c'};
    WHEN("The single char CharSet is converted to string representation") {
      std::string s = cs.toString();
      THEN(
          "The resulting string will have no unncessary delimters or "
          "parentheses") {
        REQUIRE(s == "{c}");
      }
    }
  }
  GIVEN("An empty CharSet") {
    CharSet cs;
    WHEN("The empty CharSet is converted to string representation") {
      std::string s = cs.toString();
      THEN("The string will be empty") { REQUIRE(s == ""); }
    }
  }
}