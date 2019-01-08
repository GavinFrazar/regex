#include "regex/Regex.h"

namespace Regex {
Chars::Chars() : chars() {}

Chars::Chars(std::initializer_list<char> chars) : chars(CharSet(chars)) {}

Chars::Chars(const CharSet& chars) : chars(chars) {}

std::string Chars::toString() const {
  if (chars.isEmpty()) {
    return "Ø";
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
}  // namespace Regex
