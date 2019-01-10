#include "regex/Regex.h"

#include <typeinfo>

namespace Regex {
using std::shared_ptr;

Chars::Chars() : chars() {}

Chars::Chars(const Chars &other) : chars(other.chars) {}

Chars::Chars(std::initializer_list<char> chars) : chars(CharSet(chars)) {}

Chars::Chars(std::initializer_list<CharSet::Interval> intervals)
    : chars(CharSet(intervals)) {}

Chars::Chars(const CharSet &chars) : chars(chars) {}

std::string Chars::toString() const {
  if (chars.isEmpty()) {
    return "∅";
  } else {
    return chars.toString();
  }
}

shared_ptr<Regex> Chars::clone() const {
  return shared_ptr<Chars>(new Chars(*this));
}

bool Chars::equals(const Regex &other) const {
  const Chars &other_derived = dynamic_cast<const Chars &>(other);
  return *this == other_derived;
}

std::string Concatenate::toString() const {
  return "(" + a->toString() + " ~ " + b->toString() + ")";
}

shared_ptr<Regex> Concatenate::clone() const {
  return shared_ptr<Concatenate>(new Concatenate(*this));
}

bool Concatenate::equals(const Regex &other) const {
  const Concatenate &other_derived = dynamic_cast<const Concatenate &>(other);
  return *this == other_derived;
}

std::string Union::toString() const {
  return "(" + a->toString() + " | " + b->toString() + ")";
}

shared_ptr<Regex> Union::clone() const {
  return shared_ptr<Union>(new Union(*this));
}

shared_ptr<Regex> KleeneStar::clone() const {
  return shared_ptr<KleeneStar>(new KleeneStar(*this));
}

std::string KleeneStar::toString() const { return "(" + a->toString() + ")*"; }

std::string EmptyString::toString() const { return "ε"; }

bool operator==(const Regex &a, const Regex &b) {
  if (typeid(a) == typeid(b)) {
    return a.equals(b);
  }
  return false;
}

bool operator==(const Chars &a, const Chars &b) { return a.chars == b.chars; }

bool operator==(const Concatenate &a, const Concatenate &b) {
  return (*a.a == *b.a) && (*a.b == *b.b);
}

bool operator==(const Union &a, const Union &b) {
  return (*a.a == *b.a) && (*a.b == *b.b);
}

bool operator==(const KleeneStar &a, const KleeneStar &b) {
  return *(a.a) == *(b.a);
}

}  // namespace Regex
