#include "RangeSet.h"

namespace Regex {
CharSet::CharSet(const IndexedSeq<char>& list) : RangeSet(list) {}
CharSet::CharSet(const IndexedSeq<Interval>& intervals) : RangeSet(intervals) {}
CharSet CharSet::construct(const IndexedSeq<CharSet::Interval>& v) {
  return CharSet(v);
}
}  // namespace Regex