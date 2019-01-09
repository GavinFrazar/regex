#ifndef REGEX_REGEX_H
#define REGEX_REGEX_H

#include <initializer_list>
#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include "../../src/regex/RangeSet.h"

namespace Regex {
class Regex {
 public:
  virtual std::string toString() const = 0;
  virtual std::shared_ptr<Regex> clone() const = 0;
  virtual bool equals(const Regex &other) const = 0;
};

using std::shared_ptr;
class Chars : public Regex {
 public:
  Chars();
  Chars(const Chars &other) : chars(other.chars) {}
  Chars(std::initializer_list<char> chars);
  Chars(std::initializer_list<CharSet::Interval> intervals);
  explicit Chars(const CharSet &chars);
  const CharSet chars;
  virtual std::string toString() const override;
  virtual shared_ptr<Regex> clone() const override {
    return shared_ptr<Chars>(new Chars(*this));
  }
  virtual bool equals(const Regex &other) const override;
};

class Concatenate : public Regex {
 public:
  Concatenate();                                     // default
  Concatenate(const Concatenate &other);             // copy
  friend void swap(Concatenate &a, Concatenate &b);  // swap
  Concatenate &operator=(Concatenate other);         // assignment
  Concatenate(Concatenate &&other);                  // move
  Concatenate(const Regex &a, const Regex &b);
  Concatenate(shared_ptr<Regex> a, shared_ptr<Regex> b);
  shared_ptr<Regex> a, b;
  virtual std::string toString() const override;
  virtual shared_ptr<Regex> clone() const override {
    return shared_ptr<Concatenate>(new Concatenate(*this));
  }
  virtual bool equals(const Regex &other) const override;
};

class Union : public Regex {
 public:
  Union(const Regex &a, const Regex &b);
  Union(const Union &other);
  shared_ptr<Regex> a, b;
  virtual std::string toString() const override;
  shared_ptr<Regex> clone() const override;
  // STUB
  virtual bool equals(const Regex &other) const override { return true; }
};

class KleeneStar : public Regex {
 public:
  KleeneStar(const Regex &a);
  KleeneStar(const KleeneStar &other);
  shared_ptr<Regex> a;
  virtual std::string toString() const override;
  shared_ptr<Regex> clone() const override;
  // STUB
  virtual bool equals(const Regex &other) const override { return true; }
};

// TODO: Make this a singleton.
class EmptyString : public Regex {
 public:
  EmptyString() = default;
  virtual std::string toString() const override;
  virtual shared_ptr<Regex> clone() const override {
    // STUB
    return shared_ptr<Regex>();
  }
  // STUB
  virtual bool equals(const Regex &other) const override { return true; }
};

bool operator==(const Regex &a, const Regex &b);
bool operator==(const shared_ptr<Regex> &a, const shared_ptr<Regex> &b);
bool operator==(const Chars &a, const Chars &b);
bool operator==(const Concatenate &a, const Concatenate &b);
bool operator==(const Union &a, const Union &b);
bool operator==(const KleeneStar &a, const KleeneStar &b);

}  // namespace Regex

#endif
