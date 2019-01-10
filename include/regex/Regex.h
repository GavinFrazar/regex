#ifndef REGEX_REGEX_H
#define REGEX_REGEX_H

#include <initializer_list>
#include <memory>
#include <string>
#include "regex/RangeSet.h"
#include "regex/Wrapper.h"

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

class Chars : public Regex {
 public:
  Chars() = default;
  Chars(const Chars &other) = default;
  Chars(std::initializer_list<char> chars);
  Chars(std::initializer_list<CharSet::Interval> intervals);
  explicit Chars(const CharSet &chars);
  virtual std::string toString() const override;
  virtual std::shared_ptr<Regex> clone() const override;
  const CharSet chars;

 protected:
  virtual bool equals(const Regex &other) const override;
};

class Concatenate : public Regex, public TwoMembers<Regex, Concatenate> {
 public:
  using TwoMembers<Regex, Concatenate>::TwoMembers;
  virtual std::string toString() const override;
  virtual std::shared_ptr<Regex> clone() const override;

 protected:
  virtual bool equals(const Regex &other) const override;
};

class Union : public Regex, public TwoMembers<Regex, Union> {
 public:
  using TwoMembers<Regex, Union>::TwoMembers;
  virtual std::string toString() const override;
  std::shared_ptr<Regex> clone() const override;

 protected:
  // STUB
  virtual bool equals(const Regex &other) const override;
};

class KleeneStar : public Regex {
 public:
  KleeneStar(const KleeneStar &other);
  KleeneStar(const Regex &re);
  virtual std::string toString() const override;
  std::shared_ptr<Regex> clone() const override;
  std::shared_ptr<Regex> a;

 protected:
  // STUB
  virtual bool equals(const Regex &other) const override { return true; }

 protected:
  KleeneStar(const std::shared_ptr<Regex> &sptr);
};

// TODO: Make this a singleton.
class EmptyString : public Regex {
 public:
  EmptyString() = default;
  virtual std::string toString() const override;
  virtual std::shared_ptr<Regex> clone() const override {
    // STUB
    return std::shared_ptr<Regex>();
  }

 protected:
  // STUB
  virtual bool equals(const Regex &other) const override { return true; }
};

bool operator==(const Regex &a, const Regex &b);

bool operator!=(const Regex &a, const Regex &b);

}  // namespace Regex

#endif

