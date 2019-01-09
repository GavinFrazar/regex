#ifndef REGEX_REGEX_H
#define REGEX_REGEX_H

#include <initializer_list>
#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include "../../src/regex/RangeSet.h"

namespace Regex {
/*
 *Abstract Regex class
 *Derived classes must implement a toString, clone, and equals method to get a
 *concrete class.
 */
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
  Chars(const Chars &other);
  Chars(std::initializer_list<char> chars);
  Chars(std::initializer_list<CharSet::Interval> intervals);
  explicit Chars(const CharSet &chars);
  virtual std::string toString() const override;
  virtual shared_ptr<Regex> clone() const override;
  virtual bool equals(const Regex &other) const override;
  const CharSet chars;
};

class Concatenate : public Regex {
 public:
  Concatenate();                                     // default
  Concatenate(const Concatenate &other);             // copy
  Concatenate(Concatenate &&other);                  // move
  Concatenate(const Regex &a, const Regex &b);
  Concatenate(shared_ptr<Regex> a, shared_ptr<Regex> b);
  friend void swap(Concatenate &a, Concatenate &b);  // swap
  Concatenate &operator=(Concatenate other);         // assignment
  virtual std::string toString() const override;
  virtual shared_ptr<Regex> clone() const override;
  virtual bool equals(const Regex &other) const override;
  shared_ptr<Regex> a, b;
};

class Union : public Regex {
 public:
  Union(const Regex &a, const Regex &b);
  Union(const Union &other);
  virtual std::string toString() const override;
  shared_ptr<Regex> clone() const override;
  // STUB
  virtual bool equals(const Regex &other) const override { return true; }
  shared_ptr<Regex> a, b;
};

class KleeneStar : public Regex {
 public:
  KleeneStar(const Regex &a);
  KleeneStar(const KleeneStar &other);
  virtual std::string toString() const override;
  shared_ptr<Regex> clone() const override;
  // STUB
  virtual bool equals(const Regex &other) const override { return true; }
  shared_ptr<Regex> a;
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
