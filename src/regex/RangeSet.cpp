#include "regex/RangeSet.h"

namespace Regex {
CharSet::CharSet(const IndexedSeq<Interval>& intervals) : RangeSet(intervals) {}
CharSet::CharSet(const std::initializer_list<Interval> intervals)
    : RangeSet(intervals) {}
CharSet::CharSet(const std::initializer_list<char> chars) : RangeSet(chars) {}
}  // namespace Regex
