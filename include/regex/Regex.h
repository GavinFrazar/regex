#ifndef REGEX_REGEX_H
#define REGEX_REGEX_H

#include <initializer_list>
#include <string>
#include "../../src/regex/RangeSet.h"

namespace Regex {
class Regex {
 public:
  virtual std::string toString() const = 0;
};

class Chars : public Regex {
 public:
  Chars();
  Chars(std::initializer_list<char> chars);
  Chars(std::initializer_list<CharSet::Interval> intervals);
  explicit Chars(const CharSet &chars);
  const CharSet chars;
  virtual std::string toString() const override;
};

class Concatenate : public Regex {
 public:
  Concatenate(const Regex &a, const Regex &b);
  const Regex &a;
  const Regex &b;
  virtual std::string toString() const override;
};

class Union : public Regex {
 public:
  Union(const Regex &a, const Regex &b);
  const Regex &a;
  const Regex &b;
  virtual std::string toString() const override;
};

class KleeneStar : public Regex {
 public:
  KleeneStar(const Regex &a);
  const Regex &a;
  virtual std::string toString() const override;
};

// TODO: Make this a singleton.
class EmptyString : public Regex {
 public:
  EmptyString() = default;
  virtual std::string toString() const override;
};

 bool operator==(const Chars &a, const Chars &b);
 bool operator==(const Concatenate &a, const Concatenate &b);
 bool operator==(const Union &a, const Union &b);
 bool operator==(const KleeneStar &a, const KleeneStar &b);

}  // namespace Regex

#endif
