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
 *Derived classes must implement a toString, clone, equals, nullable, and derive
 *method to get a concrete class.
 */
class Regex {
 public:
  virtual std::string toString() const = 0;
  virtual const std::shared_ptr<const Regex> clone() const = 0;
  virtual bool equals(const Regex &other) const = 0;
  virtual bool nullable() const = 0;
  bool matches(const std::string &str) const;
  virtual const std::shared_ptr<const Regex> derive(char c) const = 0;
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
  virtual bool nullable() const override;
  const CharSet chars;

 protected:
  virtual bool equals(const Regex &other) const override;
  virtual const std::shared_ptr<const Regex> derive(char c) const override;
};

class Concatenate : public Regex, public TwoMembers<Regex, Concatenate> {
 public:
  using TwoMembers<Regex, Concatenate>::TwoMembers;
  virtual std::string toString() const override;
  virtual const std::shared_ptr<const Regex> clone() const override;
  virtual bool nullable() const override;

 protected:
  virtual bool equals(const Regex &other) const override;
  virtual const std::shared_ptr<const Regex> derive(char c) const override;
};

class Union : public Regex, public TwoMembers<Regex, Union> {
 public:
  using TwoMembers<Regex, Union>::TwoMembers;
  virtual std::string toString() const override;
  const std::shared_ptr<const Regex> clone() const override;
  virtual bool nullable() const override;

 protected:
  virtual bool equals(const Regex &other) const override;
  virtual const std::shared_ptr<const Regex> derive(char c) const override;
};

class KleeneStar : public Regex {
 public:
  KleeneStar(const KleeneStar &other);
  KleeneStar(const Regex &re);
  KleeneStar(const std::shared_ptr<const Regex> &sptr);
  virtual std::string toString() const override;
  const std::shared_ptr<const Regex> clone() const override;
  const std::shared_ptr<const Regex> a;
  virtual bool nullable() const override;

 protected:
  virtual bool equals(const Regex &other) const override;
  virtual const std::shared_ptr<const Regex> derive(char c) const override;
};

class EmptyString : public Regex {
 public:
  static shared_ptr<EmptyString> getInstance() {
    static shared_ptr<EmptyString> instance(new EmptyString);
    return instance;
  }
  EmptyString(const EmptyString &) = delete;
  void operator=(const EmptyString &) = delete;
  virtual std::string toString() const override;
  virtual const std::shared_ptr<const Regex> clone() const override {
    return std::shared_ptr<const Regex>(this);
  }
  virtual bool nullable() const override;

 protected:
  EmptyString() {}
  virtual bool equals(const Regex &other) const override;
  virtual const std::shared_ptr<const Regex> derive(char c) const override;
};

bool operator==(const Regex &a, const Regex &b);

bool operator!=(const Regex &a, const Regex &b);

}  // namespace Regex

#endif
