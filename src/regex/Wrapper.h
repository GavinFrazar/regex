#ifndef REGEX_WRAPPER_H
#define REGEX_WRAPPER_H

#include <memory>

namespace Regex {

using std::shared_ptr;

template <class B, class D>
class TwoMembers {
 public:
  TwoMembers(const TwoMembers<B, D> &other);  // copy
  TwoMembers(TwoMembers &&other) = delete;    // move
  TwoMembers(const B &a, const B &b);
  template <class BASE, class DERIVED>
  friend bool operator==(const TwoMembers<B, D> &a, const TwoMembers<B, D> &b);
  const shared_ptr<const B> a, b;
};

template <class B, class D>
inline TwoMembers<B, D>::TwoMembers(const TwoMembers<B, D> &other)
    : a(other.a), b(other.b) {}

template <class B, class D>
inline TwoMembers<B, D>::TwoMembers(const B &a, const B &b)
    : a(a.clone()), b(b.clone()) {}

}  // namespace Regex

#endif
