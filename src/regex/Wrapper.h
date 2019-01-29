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
  TwoMembers(const B &a, const shared_ptr<const B> b);
  TwoMembers(const shared_ptr<const B> a, const B &b);
  TwoMembers(const shared_ptr<const B> a, const shared_ptr<const B> b);
  const shared_ptr<const B> a, b;
};

template <class B, class D>
inline TwoMembers<B, D>::TwoMembers(const TwoMembers<B, D> &other)
    : a(other.a), b(other.b) {}

template <class B, class D>
inline TwoMembers<B, D>::TwoMembers(const B &a, const B &b)
    : a(a.clone()), b(b.clone()) {}

template <class B, class D>
inline TwoMembers<B, D>::TwoMembers(const B &a, const shared_ptr<const B> b)
    : a(a.clone()), b(b) {}

template <class B, class D>
inline TwoMembers<B, D>::TwoMembers(const shared_ptr<const B> a, const B &b)
    : a(a), b(b.clone()) {}

template <class B, class D>
inline TwoMembers<B, D>::TwoMembers(const shared_ptr<const B> a,
                                    const shared_ptr<const B> b)
    : a(a), b(b) {}

}  // namespace Regex

#endif
