#ifndef REGEX_WRAPPER_H
#define REGEX_WRAPPER_H

#include <memory>

namespace Regex {

using std::shared_ptr;
template <class B, class D>
class OneMember {
 public:
  OneMember();
  OneMember(const OneMember<B, D> &other);
  OneMember &operator=(OneMember<B, D> other);
  OneMember(OneMember &&other);
  OneMember(const B &a);
  template <class BASE, class DERIVED>
  friend void swap(OneMember<BASE, DERIVED> &a, OneMember<BASE, DERIVED>);
  shared_ptr<B> a;
};

template <class B, class D>
class TwoMembers {
 public:
  TwoMembers();                                   // default
  TwoMembers(const TwoMembers<B, D> &other);      // copy
  TwoMembers &operator=(TwoMembers<B, D> other);  // copy-assignment
  TwoMembers(TwoMembers &&other);                 // move
  TwoMembers(const B &a, const B &b);
  template <class BASE, class DERIVED>
  friend void swap(TwoMembers<BASE, DERIVED> &a,
                   TwoMembers<BASE, DERIVED> &b);  // swap
  shared_ptr<B> a, b;
};

template <class B, class D>
inline OneMember<B, D>::OneMember() {}

template <class B, class D>
inline OneMember<B, D>::OneMember(const OneMember<B, D> &other) : a(other.a) {}

template <class B, class D>
inline OneMember<B, D> &OneMember<B, D>::operator=(OneMember<B, D> other) {
  swap(*this, other);
  return *this;
}

template <class B, class D>
inline OneMember<B, D>::OneMember(OneMember<B, D> &&other) {
  swap(*this, other);
}

template <class B, class D>
inline OneMember<B, D>::OneMember(const B &a) : a(a.clone()) {}

template <class B, class D>
inline void swap(OneMember<B, D> &a, OneMember<B, D> &b) {
  using std::swap;
  swap(a.a, b.a);
  swap(a.b, b.b);
}

template <class B, class D>
inline TwoMembers<B, D>::TwoMembers() {}

template <class B, class D>
inline TwoMembers<B, D>::TwoMembers(const TwoMembers<B, D> &other)
    : a(other.a), b(other.b) {}

template <class B, class D>
inline TwoMembers<B, D> &TwoMembers<B, D>::operator=(TwoMembers<B, D> other) {
  swap(*this, other);
  return *this;
}

template <class B, class D>
inline TwoMembers<B, D>::TwoMembers(TwoMembers<B, D> &&other) {
  swap(*this, other);
}

template <class B, class D>
inline TwoMembers<B, D>::TwoMembers(const B &a, const B &b)
    : a(a.clone()), b(b.clone()) {}

template <class B, class D>
inline void swap(TwoMembers<B, D> &a, TwoMembers<B, D> &b) {
  using std::swap;
  swap(a.a, b.a);
  swap(a.b, b.b);
}

}  // namespace Regex
#endif
