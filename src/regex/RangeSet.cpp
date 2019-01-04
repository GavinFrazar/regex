#include "RangeSet.h"

namespace Regex {
CharSet::CharSet(std::initializer_list<char> list) : RangeSet(IndexedSeq<char>{list}) {}
CharSet::CharSet(const IndexedSeq<Interval>& intervals) : RangeSet(intervals) {}
CharSet CharSet::construct(const IndexedSeq<CharSet::Interval>& v) {
  return CharSet(v);
}
}  // namespace Regex