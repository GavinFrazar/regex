#include "regex/Regex.h"

#include <typeinfo>

namespace Regex {
using std::shared_ptr;

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
  return chars == other_derived.chars;
}

std::string Concatenate::toString() const {
  return "(" + a->toString() + " ~ " + b->toString() + ")";
}

shared_ptr<Regex> Concatenate::clone() const {
  return shared_ptr<Concatenate>(new Concatenate(*this));
}

bool Concatenate::equals(const Regex &other) const {
  const Concatenate &other_derived = dynamic_cast<const Concatenate &>(other);
  return (*a == *other_derived.a) && (*b == *other_derived.b);
}

std::string Union::toString() const {
  return "(" + a->toString() + " | " + b->toString() + ")";
}

shared_ptr<Regex> Union::clone() const {
  return shared_ptr<Union>(new Union(*this));
}

bool Union::equals(const Regex &other) const {
  const Union &other_derived = dynamic_cast<const Union &>(other);
  return (*a == *other_derived.a) && (*b == *other_derived.b);
}

KleeneStar::KleeneStar(const KleeneStar &other) : KleeneStar(other.clone()) {}

KleeneStar::KleeneStar(const Regex &re) : a(re.clone()) {}

shared_ptr<Regex> KleeneStar::clone() const {
  return shared_ptr<KleeneStar>(new KleeneStar(a));
}

std::string KleeneStar::toString() const { return "(" + a->toString() + ")*"; }

KleeneStar::KleeneStar(const shared_ptr<Regex> &sptr) : a(sptr) {}

std::string EmptyString::toString() const { return "ε"; }

bool operator==(const Regex &a, const Regex &b) {
  if (typeid(a) == typeid(b)) {
    return a.equals(b);
  }
  return false;
}

bool operator!=(const Regex &a, const Regex &b) { return !(a == b); }

}  // namespace Regex
