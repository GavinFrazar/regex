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
  virtual const std::shared_ptr<const Regex> clone() const = 0;
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
  virtual const std::shared_ptr<const Regex> clone() const override;
  const CharSet chars;

 protected:
  virtual bool equals(const Regex &other) const override;
};

class Concatenate : public Regex, public TwoMembers<Regex, Concatenate> {
 public:
  using TwoMembers<Regex, Concatenate>::TwoMembers;
  virtual std::string toString() const override;
  virtual const std::shared_ptr<const Regex> clone() const override;

 protected:
  virtual bool equals(const Regex &other) const override;
};

class Union : public Regex, public TwoMembers<Regex, Union> {
 public:
  using TwoMembers<Regex, Union>::TwoMembers;
  virtual std::string toString() const override;
  const std::shared_ptr<const Regex> clone() const override;

 protected:
  virtual bool equals(const Regex &other) const override;
};

class KleeneStar : public Regex {
 public:
  KleeneStar(const KleeneStar &other);
  KleeneStar(const Regex &re);
  virtual std::string toString() const override;
  const std::shared_ptr<const Regex> clone() const override;
  const std::shared_ptr<const Regex> a;

 protected:
  virtual bool equals(const Regex &other) const override;
  KleeneStar(const std::shared_ptr<const Regex> &sptr);
};

// TODO: Make this a singleton.
class EmptyString : public Regex {
 public:
  EmptyString() = default;
  virtual std::string toString() const override;
  virtual const std::shared_ptr<const Regex> clone() const override {
    // STUB
    return  std::shared_ptr<const Regex>();
  }

 protected:
  virtual bool equals(const Regex &other) const override;
};

bool operator==(const Regex &a, const Regex &b);

bool operator!=(const Regex &a, const Regex &b);

}  // namespace Regex

#endif
