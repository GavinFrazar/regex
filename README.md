# Regex (work in progress)

Regex matching in C++. Basically, I want to make a library for regex matching that will also alert if a regex is "evil" and what strings can take advantage of that, to prevent ReDOS attacks.

# Goals
* Implement a virtual machine for string matching to replace the current (recursive) implementation
* Detect ambiguity in a regex
* Use static analysis to detect so-called "evil" (exponential) regexes before matching against them
* Expose attack strings that will make a regex match take exponential time (if one exists)
