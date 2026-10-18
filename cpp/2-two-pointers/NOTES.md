# Two Pointers — Notes

The concepts come first, for a quick revision. The problem-by-problem notes are at the end, for when you want more detail.

# Concepts

## Converging pointers (opposite ends)
- Start with `l = 0`, `r = n - 1` and move them towards each other while `l < r`. Each step does O(1) work and moves at least one pointer, so the whole scan is **O(n) time, O(1) space**.
- **Invariant:** everything outside `[l, r]` has already been handled (swapped, or matched against its mirror). When the pointers meet, the whole input has been handled.
- `l < r`, not `l <= r`: with odd length the middle element is its own mirror, so it never needs a swap or a comparison. The index form of the same loop is `for (i = 0; i < n / 2; i++)` with `j = n - 1 - i`.
- The other two-pointer shape (a read pointer and a trailing write pointer moving the same way) is in the [Arrays & Hashing notes](../1-arrays_and_hashing/NOTES.md#two-pointers-on-an-array-in-place).

## Skipping elements inside the loop
- Use one `if / else if` chain per iteration: skip on the left, **or** skip on the right, **or** compare and move both. Every branch moves a pointer, so the loop ends, and the `l < r` check runs again before each access.
- The alternative is inner `while` loops (`while (l < r && !isalnum(s[l])) l++;`). They work too, but each one needs its own `l < r` guard. Without it, a string of only punctuation walks `l` off the end.
- Input with nothing left after skipping (`""`, `"  "`, `".,"`) counts as a palindrome.

## Branching on a mismatch (at most one deletion)
- At the first mismatch `s[l] != s[r]`, one of the two must go. Try **both**: `[l + 1, r]` and `[l, r - 1]`, each checked as a plain palindrome with **no** further deletions.
- Picking one side greedily ("skip left if `s[l + 1] == s[r]`") is wrong. Both skips can look fine for one step, and only one works further in: `"abbab"` needs the right skip, `"babba"` needs the left one.
- It's still O(n): the scan only branches once, then returns. Both branches together are at most two O(n) scans.
- For **at most `k`** deletions, branching naively is O(2^k · n). The standard approach (Valid Palindrome III) is DP: the string works if `n - LPS(s) <= k`, where LPS is the longest palindromic subsequence, which is O(n²).

## `size() - 1` on an empty container
- `s.size()` is `size_t` (unsigned), so for an empty string `s.size() - 1` wraps to `SIZE_MAX` and doesn't become `-1`.
- `int r = s.size() - 1;` is fine: converting to `int` gives `-1` (well-defined since C++20), so `l < r` is `0 < -1` and the loop never runs.
- These break: `while (l < s.size() - 1)` (compares against `SIZE_MAX`), `size_t r = s.size() - 1;` and `for (size_t i = n - 1; i >= 0; i--)` (an unsigned value is always `>= 0`, so the loop never ends).
- Rule: convert to a signed type **first** (`int n = s.size();`) and do the arithmetic on that.

## `<cctype>` pitfalls (`isalnum`, `tolower`, …)
- They take an `int` that must be representable as `unsigned char` (or be `EOF`). A plain `char` is signed on x86, so a byte above 127 (any UTF-8 non-ASCII byte) is negative, and passing it is **UB**. The safe form is `isalnum((unsigned char) c)`.
- `tolower` returns `int`. Storing it back into a `char` is fine for ASCII.
- `isalnum` counts letters and digits only, so `'_'`, spaces and punctuation are skipped.
- Their results depend on the C locale. For contest/interview input that's always the default `"C"` locale, so this rarely matters.

## Copy or reference for a string parameter
- `bool f(string s)` copies the string: O(n) extra space. That's fine if you mutate it (e.g. lowercase it in place) and want the caller's string left alone.
- `bool f(const string& s)` doesn't copy and accepts temporaries/literals (`f("abc")`).
- `bool f(string& s)` (non-const) **rejects** literals and temporaries, and tells the reader the function may modify the argument. Only use it when it really does, like `reverseString(vector<char>&)`.

## Standard library helpers
- `std::reverse(v.begin(), v.end())` (`<algorithm>`) or `std::ranges::reverse(v)` (C++20) reverses in place, and is the built-in answer to Reverse String.
- `string(s.rbegin(), s.rend())` builds a reversed copy. Handy for a brute-force palindrome check: `s == string(s.rbegin(), s.rend())`.
- `std::swap(a, b)` (`<utility>`) swaps two elements.

# Problems

| # | Problem | File | Approach | Time | Space |
|---|---------|------|----------|------|-------|
| 1 | Reverse String | [reverse_string.cpp](reverse_string.cpp) | Swap mirrored pairs `i` and `n - 1 - i` up to `n / 2` | O(n) | O(1) |
| 2 | Valid Palindrome | [valid_palindrome.cpp](valid_palindrome.cpp) | Lowercase a copy, then converging pointers that skip non-alphanumerics | O(n) | O(n) |
| 3 | Valid Palindrome II (one deletion) | [valid_palindrome_with_deletion.cpp](valid_palindrome_with_deletion.cpp) | Converging pointers. At the first mismatch, check both `[l + 1, r]` and `[l, r - 1]` | O(n) | O(1) |

Every file has a test harness (`main` + `runTests`) with hand-picked edge cases and a random cross-check against a brute force.

### 1. Reverse String
- **`reverseString`:** swap `str[i]` with `str[n - i - 1]` for `i < n / 2`. `n` is stored as `int` first, so there's no unsigned arithmetic.
- The `return;` at the end of a `void` function doesn't do anything and can go.
- Edge cases tested: empty and single char (`n / 2 == 0`, so the loop doesn't run), two chars (one swap), odd length (the middle char stays), even length, palindrome and all same chars (output equals input), non-letters. A random cross-check runs 1000 arrays (length 0–50) against `std::reverse`.

### 2. Valid Palindrome
- **`validPalindrome`:** lowercase every char of the copy, then run converging pointers. If `s[l]` isn't alphanumeric, `l++`. Otherwise, if `s[r]` isn't, `r--`. Otherwise compare and move both.
- Edge cases tested: empty (`r` starts at `-1`), only spaces, only punctuation (all skipped → `true`), mixed case (`"Aa"`), digits are alphanumeric (`"0P"` → `false`), digit-only strings, punctuation at one or both ends, `"a."`, underscore (not alphanumeric), the classic `"A man, a plan, a canal: Panama"` / `"race a car"`. A random cross-check runs 5000 strings (length 0–12 over `"aAbB0 ,.:"`) against a filter-and-reverse brute force.
- Possible improvements:
  - Take `const string&` and compare `tolower(s[l]) != tolower(s[r])` directly. That drops the copy and the lowercasing pass, so the extra space is O(1).
  - Cast to `unsigned char` before calling `isalnum` / `tolower`, so non-ASCII input isn't UB (see [`<cctype>` pitfalls](#cctype-pitfalls-isalnum-tolower-)).
- See [Converging pointers](#converging-pointers-opposite-ends) and [Skipping elements inside the loop](#skipping-elements-inside-the-loop).

### 3. Valid Palindrome II (one deletion)
- **`validPalindrome(s)`:** converging pointers. At the first mismatch, return `validPalindrome(s, l + 1, r) || validPalindrome(s, l, r - 1)`. If there's no mismatch, the string is already a palindrome → `true`.
- **`validPalindrome(s, l, r)`:** plain palindrome check on `[l, r]` with no skipping, so a second mismatch after the deletion correctly gives `false`.
- Both overloads now take `const string&` (they were `string&`). They don't modify the string, and this lets the tests pass string literals.
- Edge cases tested: empty, single char, two different chars (`true`: delete either), three different chars (`false`), already a palindrome (odd and even length), extra char in the middle / at the start / at the end, `"abbab"` and `"babba"` (only one skip works; see [Branching on a mismatch](#branching-on-a-mismatch-at-most-one-deletion)), needs two deletions (`"abxyzba"`), both ends wrong, a second mismatch after the skip (`"abcdeca"`), all same chars, and a long LeetCode case. A random cross-check runs 5000 strings (length 0–12 over `"abc"`) against a brute force that tries removing each index.
- A greedy variant ("skip left if `s[l + 1] == s[r]`") fails the `"abbab"` test and 35 of the random strings, so the tests catch that bug.
