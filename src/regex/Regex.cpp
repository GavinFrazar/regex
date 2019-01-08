#include "regex/Regex.h"

namespace Regex {
Chars::Chars() : chars() {}

Chars::Chars(std::initializer_list<char> chars) : chars(CharSet(chars)) {}

Chars::Chars(std::initializer_list<CharSet::Interval> intervals)
  : chars(CharSet(intervals))
{}

Chars::Chars(const CharSet& chars) : chars(chars) {}

std::string Chars::toString() const {
  if (chars.isEmpty()) {
    return "∅";
  } else {
    return chars.toString();
  }
}

Concatenate::Concatenate(const Regex& a, const Regex& b) : a(a), b(b) {}

std::string Concatenate::toString() const {
  return "(" + a.toString() + " ~ " + b.toString() + ")";
}

Union::Union(const Regex& a, const Regex& b) : a(a), b(b) {}

  std::string Union::toString() const { return "(" + a.toString() + " | "
      + b.toString() + ")";}

KleeneStar::KleeneStar(const Regex& a) : a(a) {}
  std::string KleeneStar::toString() const { return "(" + a.toString() +")*"; }
  std::string EmptyString::toString() const { return "ε"; }

  bool operator==(const Chars &a, const Chars &b){
    return a.chars == b.chars;
  }
  bool operator==(const Concatenate &a, const Concatenate &b){
    return a.a == b.a && a.b == b.b;
  }
  bool operator==(const Union &a, const Union &b){
    return a.a == b.a && a.b == b.b;
  }
  bool operator==(const KleeneStar &a, const KleeneStar &b){
    return a.a == b.a;
  }

}  // namespace Regex
