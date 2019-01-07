#ifndef REGEX_RANGESET_H
#define REGEX_RANGESET_H

#include <assert.h>
#include <algorithm>
#include <deque>
#include <initializer_list>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>

namespace Regex {

template <typename E>
using IndexedSeq = std::deque<E>;

// forward declare templates
template <class T, class D>
class RangeSet;
template <class T, class D>
bool operator==(const RangeSet<T, D> &lhs, const RangeSet<T, D> &rhs);
template <class T, class D>
bool operator!=(const RangeSet<T, D> &lhs, const RangeSet<T, D> &rhs);
template <class T, class D>
std::ostream &operator<<(std::ostream &os, const RangeSet<T, D> &m);

template <class T, class D>
class RangeSet {
 public:
  class Interval : public std::tuple<T, T> {
   public:
    using std::tuple<T, T>::tuple;
    std::string toString() const {
      T a;
      T b;
      std::tie(a, b) = *this;
      std::stringstream ss;
      ss << '(' << a << "," << b << ')';
      return ss.str();
    }
    operator std::string() { return this->toString(); }
  };
  // TODO: put these declarations in a proper order.
  bool contains(const T &elem) const;
  D operator|(const D &other) const;
  D operator&(const D &other) const;
  D operator!() const;
  std::optional<T> minElement() const;
  bool isEmpty() const;
  bool equals(const RangeSet<T, D> &other) const;
  friend bool operator==
      <T, D>(const RangeSet<T, D> &lhs, const RangeSet<T, D> &rhs);
  friend bool operator!=
      <T, D>(const RangeSet<T, D> &lhs, const RangeSet<T, D> &rhs);
  std::string toString() const;

 protected:
  RangeSet() = default;
  RangeSet(const IndexedSeq<Interval> &intervals);
  RangeSet(const std::initializer_list<Interval> intervals);
  RangeSet(const std::initializer_list<T> Ts);
  static IndexedSeq<Interval> constructIntervals(
      const std::initializer_list<T> Ts);

 private:
  const IndexedSeq<Interval> elements;
  static T saturatingIncrement(T elem);
  static T saturatingDecrement(T elem);
  static IndexedSeq<Interval> collectInCommon(IndexedSeq<Interval> rangeA,
                                              IndexedSeq<Interval> rangeB);
  static IndexedSeq<Interval> order(IndexedSeq<Interval> seq);
  static const char one = 1;
};

class CharSet : public RangeSet<char, CharSet> {
 public:
  CharSet() = default;
  explicit CharSet(const IndexedSeq<Interval> &intervals);
  explicit CharSet(const std::initializer_list<Interval> intervals);
  explicit CharSet(const std::initializer_list<char> chars);
  CharSet(const CharSet &rhs) = default;
  CharSet &operator=(const CharSet &rhs) = default;
  CharSet &operator=(CharSet &&rhs) = delete;
  CharSet(CharSet &&rhs) = delete;
  static const char minValue = 'A';  // STUB
  static const char maxValue = 'z';  // STUB
  static const char one = 1;         // STUB

 protected:
  virtual CharSet construct(const IndexedSeq<CharSet::Interval> &v) override;

 private:
};

template <class T, class D>
inline bool RangeSet<T, D>::contains(T elem) {
  for (const Interval &interval : elements) {
    if (elem >= std::get<0>(interval) && elem <= std::get<1>(interval))
      return true;
  }
  return false;
}

template <class T, class D>
inline D RangeSet<T, D>::operator|(const D &other) {
  IndexedSeq<Interval> temp(elements);
  temp.insert(temp.end(), other.elements.begin(), other.elements.end());
  return construct(temp);
}

template <class T, class D>
inline D RangeSet<T, D>::operator&(const D &other) {
  return construct(collectInCommon(elements, other.elements));
}

template <class T, class D>
inline D RangeSet<T, D>::operator!() {
  using std::tie, std::ignore;
  if (elements.empty()) {
    return construct({Interval(D::minValue, D::maxValue)});
  } else {
    IndexedSeq<Interval> newFirst;
    T min;
    tie(min, ignore) = elements.front();
    if (min != D::minValue) {
      newFirst.push_back(Interval(min, min - D::one));
    }

    IndexedSeq<Interval> newLast;
    T max;
    tie(ignore, max) = elements.back();
    if (max != D::maxValue) {
      newLast.push_back(Interval(max + D::one, D::maxValue));
    }

    IndexedSeq<Interval> newMiddle;
    if (elements.size() > 1) {
      for (IndexedSeq<Interval>::const_iterator it = elements.begin();
           it + 1 != elements.end(); ++it) {
        T leftMax;
        T rightMin;
        tie(ignore, leftMax) = *it;
        tie(rightMin, ignore) = *(it + 1);
        assert(leftMax != D::maxValue && rightMin != D::minValue);
        newMiddle.push_back(Interval(leftMax + D::one, rightMin - D::one));
      }
    }
    newFirst.insert(newFirst.end(), newMiddle.begin(), newMiddle.end());
    newFirst.insert(newFirst.end(), newLast.begin(), newLast.end());
    return construct(newFirst);
  }
}

template <class T, class D>
inline std::optional<T> RangeSet<T, D>::minElement() {
  if (elements.empty())
    return {};
  else
    return ::std::get<0>(elements.front());
}

template <class T, class D>
inline bool RangeSet<T, D>::isEmpty() {
  return elements.empty();
}

template <class T, class D>
inline bool RangeSet<T, D>::equals(const RangeSet<T, D> &other) {
  return *this == other;
}

template <class T, class D>
inline RangeSet<T, D>::RangeSet(const IndexedSeq<Interval> &seq)
    : contents(seq), elements(order(seq)) {}

template <class T, class D>
inline RangeSet<T, D>::RangeSet(const IndexedSeq<T> &list)
    : RangeSet(construct(list)) {}

template <class T, class D>
inline std::string RangeSet<T, D>::toString() {
  if (this->isEmpty()) {
    return std::string();
  } else {
    using std::tie;
    std::stringstream ss;
    ss << '{';
    std::for_each(elements.begin(), elements.end() - 1,
                  [&ss](const auto &interval) -> void {
                    T a;
                    T b;
                    tie(a, b) = interval;
                    if (a == b)
                      ss << a;
                    else
                      ss << interval.toString();
                    ss << ", ";
                  });
    T a;
    T b;
    tie(a, b) = elements.back();
    if (a == b)
      ss << a;
    else
      ss << elements.back().toString();
    ss << '}';
    return ss.str();
  }
}

template <class T, class D>
inline IndexedSeq<typename RangeSet<T, D>::Interval> RangeSet<T, D>::construct(
    const IndexedSeq<T> &list) {
  IndexedSeq<Interval> intervals;
  for (const auto &elem : list) {
    intervals.push_back(Interval(elem, elem));
  }
  return intervals;
}

template <class T, class D>
inline bool operator==(const RangeSet<T, D> &lhs, const RangeSet<T, D> &rhs) {
  return lhs.elements == rhs.elements;
}

template <class T, class D>
inline T RangeSet<T, D>::saturatingIncrement(T elem) {
  return elem == D::maxValue ? elem : elem + one;
}

template <class T, class D>
inline T RangeSet<T, D>::saturatingDecrement(T elem) {
  return elem == D::minValue ? elem : elem - one;
}

template <class T, class D>
inline IndexedSeq<typename RangeSet<T, D>::Interval>
RangeSet<T, D>::collectInCommon(IndexedSeq<RangeSet<T, D>::Interval> rangeA,
                                IndexedSeq<RangeSet<T, D>::Interval> rangeB) {
  IndexedSeq<Interval> soFar;
  while (!rangeA.empty() && !rangeB.empty()) {
    const T &minA = std::get<0>(rangeA.front());
    const T &maxA = std::get<1>(rangeA.front());
    const T &minB = std::get<0>(rangeB.front());
    const T &maxB = std::get<1>(rangeB.front());
    if (maxA < minB) {
      rangeA.pop_front();
    } else if (maxB < minA) {
      rangeB.pop_front();
    } else {
      const T &newMin = (minA < minB) ? minB : minA;
      const T &newMax = (maxA > maxB) ? maxB : maxA;
      soFar.push_back(Interval(newMin, newMax));
      if (newMax >= maxA)
        rangeA.pop_front();
      else
        rangeB.pop_front();
    }
  }
  return soFar;
}

template <class T, class D>
inline IndexedSeq<typename RangeSet<T, D>::Interval> RangeSet<T, D>::order(
    IndexedSeq<Interval> seq) {
  using std::tie;
  std::sort(seq.begin(), seq.end());
  IndexedSeq<Interval> acc;
  for (const Interval &interval : seq) {
    if (acc.empty()) {
      acc.push_back(interval);
    } else {
      T min, max;
      tie(min, max) = interval;
      T prevMin, prevMax;
      tie(prevMin, prevMax) = acc.back();
      if (prevMax >= max) {
        continue;
      } else if (prevMax >= saturatingDecrement(min)) {
        acc.pop_back();
        acc.push_back(Interval(prevMin, max));
      } else {
        acc.push_back(interval);
      }
    }
  }
  return acc;
}

}  // namespace Regex

#endif