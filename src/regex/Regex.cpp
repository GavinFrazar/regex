#include "regex/Regex.h"

namespace Regex {
Chars::Chars() : chars() {}

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

bool Chars::equals(const Regex &other) const {
  const Chars &other_derived = dynamic_cast<const Chars &>(other);
  return *this == other_derived;
}

Concatenate::Concatenate(const Regex &a, const Regex &b)
    : a(a.clone()), b(b.clone()) {}

Concatenate::Concatenate(const Concatenate &other)
    : a(other.a->clone()), b(other.b->clone()) {}

std::string Concatenate::toString() const {
  return "(" + a->toString() + " ~ " + b->toString() + ")";
}

bool Concatenate::equals(const Regex &other) const {
  const Concatenate &other_derived = dynamic_cast<const Concatenate &>(other);
  return *this == other_derived;
}

Union::Union(const Regex &a, const Regex &b) : a(a.clone()), b(b.clone()) {}

Union::Union(const Union &other) : a(other.a->clone()), b(other.b->clone()) {}

std::string Union::toString() const {
  return "(" + a->toString() + " | " + b->toString() + ")";
}

unique_ptr<Regex> Union::clone() const {
  return unique_ptr<Union>(new Union(*this));
}

KleeneStar::KleeneStar(const Regex &a) : a(a.clone()) {}

KleeneStar::KleeneStar(const KleeneStar &other) : a(other.a->clone()) {}

unique_ptr<Regex> KleeneStar::clone() const {
  return unique_ptr<KleeneStar>(new KleeneStar(*this));
}

std::string KleeneStar::toString() const { return "(" + a->toString() + ")*"; }

std::string EmptyString::toString() const { return "ε"; }

bool operator==(const Regex &a, const Regex &b) {
  if (typeid(a) == typeid(b)) {
    return a.equals(b);
  }
  return false;
}

bool operator==(const unique_ptr<Regex> &a, const unique_ptr<Regex> &b) {
  return *a == *b;
}
bool operator==(const Chars &a, const Chars &b) { return a.chars == b.chars; }

bool operator==(const Concatenate &a, const Concatenate &b) {
  return *(a.a) == *(b.a);
}

bool operator==(const Union &a, const Union &b) {
  return *(a.a) == *(b.a) && *(a.b) == *(b.b);
}

bool operator==(const KleeneStar &a, const KleeneStar &b) {
  return *(a.a) == *(b.a);
}

}  // namespace Regex
