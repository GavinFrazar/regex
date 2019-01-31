#include <catch2/catch.hpp>

#include <iostream>
#include "regex/Regex.h"
using Regex::Chars;
using Regex::Concatenate;
using Regex::EmptyString;
using Regex::KleeneStar;
using Regex::Regex;
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
  GIVEN("A Union of Char regex") {
    Union re(a, b);
    WHEN("The union regex is converted to a string") {
      auto s = re.toString();
      THEN("The string will be the union of the a and b Chars") {
        REQUIRE(s == "({a} | {b})");
      }
    }
  }
  GIVEN("A KleeneStar of a Char") {
    KleeneStar re(a);
    WHEN("The KleeneStar regex is converted to a string") {
      auto s = re.toString();
      THEN("The string will be the kleenestar of the a Char") {
        REQUIRE(s == "({a})*");
      }
    }
  }
  GIVEN("The empty string regex") {
    auto re = EmptyString::getInstance();
    WHEN("The empty string regex is converted to a string") {
      auto s = re->toString();
      THEN("The string will be epsilon") { REQUIRE(s == "ε"); }
    }
  }
}

SCENARIO("Comparing two regex for equality") {
  GIVEN("Two Char regex") {
    Chars a = {'a'};
    Chars b = {'b'};
    WHEN("Chars a is compared with a") {
      bool equal = a == a;
      THEN("The regex should be equal") { REQUIRE(equal); }
    }
    WHEN("Chars a is compared with b") {
      bool equal = a == b;
      THEN("The regex should not be equal") { REQUIRE_FALSE(equal); }
    }
  }
  GIVEN("Some Concatenate regex") {
    Concatenate re1(Chars{'a'}, Chars{'a'});
    Concatenate re2(Chars{'b'}, Chars{'b'});
    Concatenate re3(Chars{'a'}, Chars{'b'});
    Concatenate re4(Chars{'b'}, Chars{'a'});
    Concatenate re5(Chars{'a'}, Chars{'a'});
    Chars c = {'c'}, d = {'d'};
    Concatenate re6(c, d), re7(c, d);
    WHEN(re1.toString() + " is compared with " + re1.toString()) {
      bool equal = re1 == re1;
      THEN("The regex should be equal") { REQUIRE(equal); }
    }
    WHEN(re1.toString() + " is compared with " + re5.toString()) {
      bool equal = re1 == re5;
      THEN("The regex should be equal") { REQUIRE(re1 == re5); }
    }
    WHEN(re1.toString() + " is compared with " + re2.toString()) {
      bool equal = re1 == re2;
      THEN("The regex should not be equal") { REQUIRE_FALSE(equal); }
    }
    WHEN(re1.toString() + " is compared with " + re3.toString()) {
      bool equal = re1 == re3;
      THEN("The regex should not be equal") { REQUIRE_FALSE(equal); }
    }
    WHEN(re1.toString() + " is compared with " + re4.toString()) {
      bool equal = re1 == re4;
      THEN("The regex should not be equal") { REQUIRE_FALSE(equal); }
    }
    WHEN(re3.toString() + " is compared with " + re4.toString()) {
      bool equal = re3 == re4;
      THEN("The regex should not be equal") { REQUIRE_FALSE(equal); }
    }
    WHEN(re6.toString() + " is compared with " + re7.toString()) {
      bool equal = re6 == re7;
      THEN("The regex should be equal") { REQUIRE(equal); }
    }
  }
  GIVEN("Some Union regex") {
    Chars a = {'a'}, b = {'b'};
    Union re1(a, b), re2(b, a);
    Union re3(a, a), re4(b, b);
    WHEN(re1.toString() + " is compared with " + re2.toString()) {
      bool equal = re1 == re2;
      THEN("The regex should be equal") { REQUIRE(equal); }
    }
    WHEN(re1.toString() + " is compared with " + re1.toString()) {
      bool equal = re1 == re1;
      THEN("The regex should be equal") { REQUIRE(equal); }
    }
    WHEN(re1.toString() + " is compared with " + re3.toString()) {
      bool equal = re1 == re3;
      THEN("The regex should not be equal") { REQUIRE_FALSE(equal); }
    }
    WHEN(re1.toString() + " is compared with " + re4.toString()) {
      bool equal = re1 == re4;
      THEN("The regex should not be equal") { REQUIRE_FALSE(equal); }
    }
    WHEN(re2.toString() + " is compared with " + re3.toString()) {
      bool equal = re2 == re3;
      THEN("The regex should not be equal") { REQUIRE_FALSE(equal); }
    }
    WHEN(re2.toString() + " is compared with " + re4.toString()) {
      bool equal = re2 == re4;
      THEN("The regex should not be equal") { REQUIRE_FALSE(equal); }
    }
  }
}

SCENARIO("Determine if a regex is nullable") {
  GIVEN("Some Regexes") {
    Chars a = {'a'}, b = {'b'};
    auto e = EmptyString::getInstance();
    WHEN(a.toString() + " is tested for nullable") {
      bool nullable = a.nullable();
      THEN("The regex is not nullable") { REQUIRE_FALSE(nullable); }
    }
    WHEN(e->toString() + " is tested for nullable") {
      bool nullable = e->nullable();
      THEN("The EmptyString should be nullable") { REQUIRE(nullable); }
    }
    WHEN("a is concatenated with b") {
      Concatenate c(a, b);
      THEN("The concatenation is not nullable") { REQUIRE_FALSE(c.nullable()); }
    }
    WHEN("a is concatenated with EmptyString") {
      Concatenate c(a, e);
      THEN("The concatenation is not nullable") { REQUIRE_FALSE(c.nullable()); }
    }
    WHEN("EmptyString is concatenated with a") {
      Concatenate c(e, a);
      THEN("The concatenation is not nullable") { REQUIRE_FALSE(c.nullable()); }
    }
    WHEN("EmptyString is concatenated with EmptyString") {
      Concatenate c(e, e);
      THEN("The concatenation is nullable") { REQUIRE(c.nullable()); }
    }
    WHEN("a is unioned with b") {
      Union u(a, b);
      THEN("The union is not nullable") { REQUIRE_FALSE(u.nullable()); }
    }
    WHEN("a is unioned with EmptyString") {
      Union u(a, e);
      THEN("The union is nullable") { REQUIRE(u.nullable()); }
    }
    WHEN("EmptyString is unioned with a") {
      Union u(e, a);
      THEN("The union is nullable") { REQUIRE(u.nullable()); }
    }
    WHEN("EmptyString is unioned with EmptyString") {
      Union u(e, e);
      THEN("The union is nullable") { REQUIRE(u.nullable()); }
    }
    WHEN("a is KleeneStarred") {
      KleeneStar k(a);
      THEN("The kleenestar is nullable") { REQUIRE(k.nullable()); }
    }
    WHEN("EmptyString is KleeneStarred") {
      KleeneStar k(e);
      THEN("The KleeneStar is nullable") { REQUIRE(k.nullable()); }
    }
  }
}

SCENARIO("Matching a simple string") {
  Chars a = {'a'}, b = {'b'};
  GIVEN("Simple chars") {
    WHEN(a.toString() + " tries to match \"a\"") {
      bool matched = a.matches("a");
      THEN("It matches the string") { REQUIRE(matched); }
    }
    WHEN(a.toString() + R"( tries to match "b")") {
      bool matched = a.matches("b");
      THEN("It does not match the string") { REQUIRE_FALSE(matched); }
    }
  }
  GIVEN("A simple Concatenation") {
    Concatenate c(a, b);
    WHEN(c.toString() + R"( tries to match "ab")") {
      bool matched = c.matches("ab");
      THEN("It matches the string") { REQUIRE(matched); }
    }
    WHEN(c.toString() + R"( tries to match "")") {
      bool matched = c.matches("");
      THEN("It does not match the empty string") { REQUIRE_FALSE(matched); }
    }
    WHEN(c.toString() + R"( tries to match "aa")") {
      bool matched = c.matches("aa");
      THEN("It does not match the string") { REQUIRE_FALSE(matched); }
    }
  }
  GIVEN("A simple Union") {
    Union u(a, b);
    WHEN(u.toString() + R"( tries to match "a")") {
      bool matched = u.matches("a");
      THEN("It matches the string") { REQUIRE(matched); }
    }
    WHEN(u.toString() + R"( tries to match "b")") {
      bool matched = u.matches("b");
      THEN("It matches the string") { REQUIRE(matched); }
    }
    WHEN(u.toString() + R"( tries to match "")") {
      bool matched = u.matches("");
      THEN("It does not match the string") { REQUIRE_FALSE(matched); }
    }
    WHEN(u.toString() + R"( tries to match "ab")") {
      bool matched = u.matches("ab");
      THEN("It does not match the string") { REQUIRE_FALSE(matched); }
    }
    WHEN(u.toString() + R"( tries to match "aa")") {
      bool matched = u.matches("aa");
      THEN("It matches the string") { REQUIRE_FALSE(matched); }
    }
    WHEN(u.toString() + R"( tries to match "bb")") {
      bool matched = u.matches("bb");
      THEN("It matches the string") { REQUIRE_FALSE(matched); }
    }
  }
  GIVEN("A simple KleeneStar") {
    KleeneStar k(a);
    WHEN(k.toString() + R"( tries to match "")") {
      bool matched = k.matches("");
      THEN("It matches the empty string") { REQUIRE(matched); }
    }
    WHEN(k.toString() + R"( tries to match "a")") {
      bool matched = k.matches("a");
      THEN("It matches the string") { REQUIRE(matched); }
    }
    WHEN(k.toString() + R"( tries to match "aaaaaa")") {
      bool matched = k.matches("aaaaaa");
      THEN("It matches the string") { REQUIRE(matched); }
    }
    WHEN(k.toString() + R"( tries to match "b")") {
      bool matched = k.matches("b");
      THEN("It does not match the string") { REQUIRE_FALSE(matched); }
    }
    WHEN(k.toString() + R"( tries to match "ab")") {
      bool matched = k.matches("ab");
      THEN("It does not match the string") { REQUIRE_FALSE(matched); }
    }
    WHEN(k.toString() + R"( tries to match "aaab")") {
      bool matched = k.matches("aaab");
      THEN("It does not match the string") { REQUIRE_FALSE(matched); }
    }
  }
}
