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

const shared_ptr<const Regex> Chars::clone() const {
  return shared_ptr<const Chars>(new Chars(*this));
}

bool Chars::equals(const Regex &other) const {
  auto other_derived = dynamic_cast<const Chars &>(other);
  return chars == other_derived.chars;
}

std::string Concatenate::toString() const {
  return "(" + a->toString() + " ~ " + b->toString() + ")";
}

const shared_ptr<const Regex> Concatenate::clone() const {
  return shared_ptr<const Concatenate>(new Concatenate(*this));
}

bool Concatenate::equals(const Regex &other) const {
  auto other_derived = dynamic_cast<const Concatenate &>(other);
  return (*a == *other_derived.a) && (*b == *other_derived.b);
}

std::string Union::toString() const {
  return "(" + a->toString() + " | " + b->toString() + ")";
}

const shared_ptr<const Regex> Union::clone() const {
  return shared_ptr<const Union>(new Union(*this));
}

bool Union::equals(const Regex &other) const {
  auto other_derived = dynamic_cast<const Union &>(other);
  // TODO -- make Union construction follow specific ordering to avoid
  // backtracking for expensive (deep) comparisons
  return ((*a == *other_derived.a) && (*b == *other_derived.b) ||
          (*a == *other_derived.b && *b == *other_derived.a));
}

KleeneStar::KleeneStar(const KleeneStar &other) : KleeneStar(other.clone()) {}

KleeneStar::KleeneStar(const Regex &re) : a(re.clone()) {}

std::string KleeneStar::toString() const { return "(" + a->toString() + ")*"; }

const shared_ptr<const Regex> KleeneStar::clone() const {
  return shared_ptr<const KleeneStar>(new KleeneStar(a));
}

bool KleeneStar::equals(const Regex &other) const {
  auto other_derived = dynamic_cast<const KleeneStar &>(other);
  return *a == *other_derived.a;
}

KleeneStar::KleeneStar(const shared_ptr<const Regex> &sptr) : a(sptr) {}

std::string EmptyString::toString() const { return "ε"; }

bool EmptyString::equals(const Regex &other) const {
  // other is assumed to be of same type in this method
  // EmptyString is always equal to itself
  return true;
}
bool operator==(const Regex &a, const Regex &b) {
  if (typeid(a) == typeid(b)) {
    return a.equals(b);
  }
  return false;
}

bool operator!=(const Regex &a, const Regex &b) { return !(a == b); }

}  // namespace Regex
