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

## Merging two sequences (one pointer each)
- Keep one pointer per input. Loop **while both** have elements left, take one element per step, then **drain the leftover tail**. At most one tail is non-empty, so writing both drain loops is fine and needs no `if`.
- Merge Sorted Array chooses by comparing. Merge Strings Alternately uses a fixed rule (take from `s1`, then from `s2`). The loop has the same shape either way.
- Reserve the output size up front when you know it (`res.reserve(n + m)`), so appending doesn't reallocate.

## Merging in place from the back
- When the output overlaps an input (`nums1` has `m` spare slots at its end), fill it **from the back**: the largest remaining element goes to `curr = n + m - 1`, then `curr--`.
- Why it's safe: `curr == p1 + p2 + 1`, so while `nums2` still has elements (`p2 >= 0`), `curr > p1`, and a write never overwrites an unread `nums1` element. Going front to back would overwrite them, unless you first copy `nums1` (O(n) extra space).
- Once `nums2` runs out, the remaining `nums1` elements are already in place, so **only the `p2` tail needs draining**.
- Move with assignment (`nums1[curr--] = nums2[p2--]`), not `swap`. Assignment is one write instead of three, and `swap` also overwrites the caller's `nums2` with whatever was in the placeholder slots.

## Fix one element, two-pointer the rest (3Sum)
- Sort, then for each `i` run converging pointers on `[i + 1, n - 1]` looking for `-nums[i]`. That's O(n) per `i`, so **O(n²)** in total, and the O(n log n) sort doesn't change that.
- Why converging works on sorted input: if the sum is too big, `nums[r]` is too big even with the smallest remaining `nums[l]`, so drop `r`. If it's too small, drop `l` for the same reason. Each step rules out one candidate.
- **Skipping repeats without a `set`:** skip `i` when `nums[i] == nums[i - 1]`. After a match, move `l` past values equal to the one just used. Skipping repeats for `r` is optional: a repeated `nums[r]` fails the next sum check and moves on anyway.
- **Stop early:** once `nums[i] > 0`, everything after it is positive too, so no triplet can sum to 0.
- `nums[i] + nums[l] + nums[r]` can overflow `int` for large values. Use `long long` when the values aren't bounded.
- The same idea gives kSum: fix `k - 2` elements (loops or recursion), then two-pointer the rest, for O(n^(k-1)).
- **kSum by recursion:** `kSum(k, target, l)` loops `i` from `l` (skipping repeats) and calls `kSum(k - 1, target - nums[i], i + 1)`. The base case `k == 2` is the converging two pointers. Keep the values chosen so far in a `vector` used as a stack (`push_back` before the call, `pop_back` after). One helper then solves 2Sum, 3Sum and 4Sum.
- **Stopping early in kSum (sorted input):** any `k` elements from `[l, r]` sum to at most `nums[r] * k`, so return if that's below `target`. In the loop, `k` elements starting at `nums[i]` sum to at least `nums[i] * k`, so `break` once that's above `target`. Do the multiplication in `long long`.

## Take out, then put back (count maps)
- A common pattern is to remove an element from a count map (`mp[x]--`), do some work, and put it back (`mp[x]++`). Any `continue`, `break` or `return` between the two skips the restore, and the counts drift lower every time it happens.
- Do the skip checks **before** the `--`, so every `--` is always followed by its `++`.

## Unqualified `swap` and ADL
- `swap(a, b)` with no `std::` and no `using std::swap;` **doesn't compile for `int`s**. Argument-dependent lookup (ADL) only searches the namespaces of the argument types, and built-in types like `int` have none.
- It *does* compile when an argument is a `std::` type (e.g. `std::string`, `std::vector`), because ADL then finds `std::swap`. So the same line can compile in one file and fail in another.
- The idiom: `using std::swap; swap(a, b);`. A type's own `swap` (found by ADL) wins if it has one, and `std::swap` is the fallback. Or just write `std::swap(a, b)`.

## `operator[]` on a map inserts missing keys
- `mp[key]` on a `map` / `unordered_map` inserts `key` with a default value (`0` for `int`) if it's missing. A lookup like `if (mp[target] > 0)` therefore adds an entry on every miss. Over an O(n²) loop that can grow the map to O(n²) entries.
- For a pure lookup, use `auto it = mp.find(key); if (it != mp.end() && it->second > 0)`, or `mp.contains(key)` (C++20) / `mp.count(key)`. `operator[]` also doesn't work on a `const` map.

## Signed overflow: the type comes from the operands
- The type of an arithmetic expression comes from its **operands**, not from the variable it's stored in. In `long long sum = a + b + c;` with `int`s, every `+` is done in `int`, and the result is converted only after it has already overflowed.
- Cast **before the first `+`**: `(long long) a + b + c`. Addition goes left to right (`(a + b) + c`), so the cast must apply to the leftmost operand. `a + b + (long long) c` still overflows on `a + b`, and `(long long) (a + b + c)` casts too late.
- Mixing is fine once one side is wide: `int - long long` promotes the `int`, so `target - sum` is done in 64 bits.
- Signed overflow is **undefined behavior**, so the compiler may assume it never happens. Results then depend on the compiler: GCC wraps here and gives a wrong answer, while Clang may widen the add to 64 bits and accidentally get it right. **Passing on LeetCode doesn't prove there's no overflow.**
- `long` is 64 bits on Linux/macOS but **32 bits on Windows (MSVC)**. Use `long long` (at least 64 bits everywhere) or `int64_t` from `<cstdint>` (exactly 64).
- When you look up a 64-bit value in a map, give the map a 64-bit key. With `unordered_map<int, int>`, `mp.find(x)` silently converts an out-of-range `long long x` to `int`, which wraps it and can match a real key.
- To catch overflow at runtime without the sanitizer runtime libraries: `g++ -fsanitize=signed-integer-overflow -fsanitize-trap=all`. The program stops (SIGILL, exit code 132) at the first overflow.

## `size() - 1` on an empty container
- `s.size()` is `size_t` (unsigned), so for an empty string `s.size() - 1` wraps to `SIZE_MAX` and doesn't become `-1`.
- `int r = s.size() - 1;` is fine: converting to `int` gives `-1` (well-defined since C++20), so `l < r` is `0 < -1` and the loop never runs.
- These break: `while (l < s.size() - 1)` (compares against `SIZE_MAX`), `size_t r = s.size() - 1;` and `for (size_t i = n - 1; i >= 0; i--)` (an unsigned value is always `>= 0`, so the loop never ends).
- Rule: convert to a signed type **first** (`int n = s.size();`) and do the arithmetic on that.
- `int p < s.size()` triggers `-Wsign-compare`, because `p` is converted to unsigned for the comparison. That's harmless while `p >= 0`, but a negative `p` becomes huge and the check passes when it shouldn't. Storing `int n = s.size();` once also removes the warning, so real warnings don't get lost in the noise.

## `<cctype>` pitfalls (`isalnum`, `tolower`, …)
- They take an `int` that must be representable as `unsigned char` (or be `EOF`). A plain `char` is signed on x86, so a byte above 127 (any UTF-8 non-ASCII byte) is negative, and passing it is **UB**. The safe form is `isalnum((unsigned char) c)`.
- `tolower` returns `int`. Storing it back into a `char` is fine for ASCII.
- `isalnum` counts letters and digits only, so `'_'`, spaces and punctuation are skipped.
- Their results depend on the C locale. For contest/interview input that's always the default `"C"` locale, so this rarely matters.

## `vector` over `list` (the default container)
- Reach for `std::vector` first. It stores elements contiguously, so walking it is cache-friendly and the hardware prefetcher can help. `push_back` / `pop_back` are amortized O(1), and with `reserve(n)` there's no reallocation at all.
- `std::list` is a doubly linked list. **Every insert allocates a separate node** (about 2 extra pointers per element, plus allocator overhead), and the nodes are scattered in memory, so each step of a traversal is a likely cache miss. Even when the big-O is the same, it's usually several times slower.
- For a stack of current choices in backtracking or kSum, use `vector<int>` with `push_back` / `pop_back`. Copying it into the result is then just `res.push_back(curr)`, with no `vector(list.begin(), list.end())` conversion.
- `list` only wins when you need its specific guarantees: O(1) insert/erase **in the middle** at an iterator you already hold, iterators that stay valid while other elements are inserted or erased, or `splice`. Example: the recency list in an LRU cache.
- In C++ interviews (HFT especially), `std::list` without a reason usually prompts "why not a vector?".

## Copy or reference for a string parameter
- `bool f(string s)` copies the string: O(n) extra space. That's fine if you mutate it (e.g. lowercase it in place) and want the caller's string left alone. If the function only reads `s`, the copy is wasted.
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
| 2 | Valid Palindrome | [valid_palindrome.cpp](valid_palindrome.cpp) | Converging pointers that skip non-alphanumerics and compare with `tolower` | O(n) | O(1) |
| 3 | Valid Palindrome II (one deletion) | [valid_palindrome_with_deletion.cpp](valid_palindrome_with_deletion.cpp) | Converging pointers. At the first mismatch, check both `[l + 1, r]` and `[l, r - 1]` | O(n) | O(1) |
| 4 | Merge Strings Alternately | [merge_alt_string.cpp](merge_alt_string.cpp) | One pointer per string, alternate while both have chars, then append the leftover tail | O(n + m) | O(1) extra (output aside) |
| 5 | Merge Sorted Array | [merge_sorted_array.cpp](merge_sorted_array.cpp) | Fill `nums1` from the back with the larger of `nums1[p1]` / `nums2[p2]`, then drain `nums2` | O(n + m) | O(1) |
| 6 | 3Sum | [3_sum.cpp](3_sum.cpp) | Sort, fix `nums[i]`, converging pointers on the rest for `-nums[i]`, skip repeats | O(n²) | O(1) extra (sort and output aside) |
| 7 | 4Sum | [4_sum.cpp](4_sum.cpp) | Sort, then recursive kSum: fix one element per level, converging pointers when `k == 2`. (Also hashed: fix `i < j < k`, look up `target - sum` after `k`) | O(n³) | O(k) extra (output aside); hashed O(n) |

Every file has a minimal test harness (`main` + `runTests`, plus `checkAll` when there are several implementations) with hand-picked edge cases and a random cross-check against a brute force.

### 1. Reverse String
- **`reverseString`:** swap `str[i]` with `str[n - i - 1]` for `i < n / 2`. `n` is stored as `int` first, so there's no unsigned arithmetic.
- The `return;` at the end of a `void` function doesn't do anything and can go.
- Edge cases tested: empty and single char (`n / 2 == 0`, so the loop doesn't run), two chars (one swap), odd length (the middle char stays), even length, palindrome and all same chars (output equals input), non-letters. A random cross-check runs 1000 arrays (length 0–50) against `std::reverse`.

### 2. Valid Palindrome
- **`validPalindrome`:** converging pointers. If `s[l]` isn't alphanumeric, `l++`. Otherwise, if `s[r]` isn't, `r--`. Otherwise compare `tolower(s[l++]) != tolower(s[r--])` and move both.
- An earlier version took `string s` by value and lowercased the whole copy first: O(n) extra space and one extra pass. Comparing with `tolower` directly means nothing modifies `s`, so it now takes `const string&`, and the extra space is O(1) (see [Copy or reference for a string parameter](#copy-or-reference-for-a-string-parameter)).
- Edge cases tested: empty (`r` starts at `-1`), only spaces, only punctuation (all skipped → `true`), mixed case (`"Aa"`), digits are alphanumeric (`"0P"` → `false`), digit-only strings, punctuation at one or both ends, `"a."`, underscore (not alphanumeric), the classic `"A man, a plan, a canal: Panama"` / `"race a car"`. A random cross-check runs 5000 strings (length 0–12 over `"aAbB0 ,.:"`) against a filter-and-reverse brute force.
- The input is guaranteed to be printable ASCII, so passing a plain `char` to `isalnum` / `tolower` is safe here. Without that guarantee, cast to `unsigned char` first (see [`<cctype>` pitfalls](#cctype-pitfalls-isalnum-tolower-)).
- See [Converging pointers](#converging-pointers-opposite-ends) and [Skipping elements inside the loop](#skipping-elements-inside-the-loop).

### 3. Valid Palindrome II (one deletion)
- **`validPalindrome(s)`:** converging pointers. At the first mismatch, return `validPalindrome(s, l + 1, r) || validPalindrome(s, l, r - 1)`. If there's no mismatch, the string is already a palindrome → `true`.
- **`validPalindrome(s, l, r)`:** plain palindrome check on `[l, r]` with no skipping, so a second mismatch after the deletion correctly gives `false`.
- Both overloads now take `const string&` (they were `string&`). They don't modify the string, and this lets the tests pass string literals.
- Edge cases tested: empty, single char, two different chars (`true`: delete either), three different chars (`false`), already a palindrome (odd and even length), extra char in the middle / at the start / at the end, `"abbab"` and `"babba"` (only one skip works; see [Branching on a mismatch](#branching-on-a-mismatch-at-most-one-deletion)), needs two deletions (`"abxyzba"`), both ends wrong, a second mismatch after the skip (`"abcdeca"`), all same chars, and a long LeetCode case. A random cross-check runs 5000 strings (length 0–12 over `"abc"`) against a brute force that tries removing each index.
- A greedy variant ("skip left if `s[l + 1] == s[r]`") fails the `"abbab"` test and 35 of the random strings, so the tests catch that bug.

### 4. Merge Strings Alternately
- **`mergeAlternateStrings`:** pointers `p1` and `p2` plus a counter `i`. Even `i` takes from `s1` and odd `i` from `s2`, while both have chars left. Then both tails are drained (only one is non-empty). See [Merging two sequences](#merging-two-sequences-one-pointer-each).
- The `i % 2` toggle isn't needed. Each iteration can take one char from each string (`res += s1[p1++]; res += s2[p2++];`). Or use a single index: `for (i = 0; i < max(n, m); i++) { if (i < n) res += s1[i]; if (i < m) res += s2[i]; }`, which handles the tails too.
- It takes both strings **by value**, so each call copies them. It only reads them, so use `const string&` (see [Copy or reference for a string parameter](#copy-or-reference-for-a-string-parameter); this slip also came up in Valid Palindrome).
- `p1 < s1.size()` compares `int` with `size_t` and triggers 4 `-Wsign-compare` warnings (see [`size() - 1` on an empty container](#size---1-on-an-empty-container)).
- Edge cases tested: both empty, one empty, single chars, equal length (no tail), `s1` or `s2` longer, longer by exactly one, one char vs a long string, repeated chars (catches taking from the wrong string). A random cross-check runs 5000 pairs (lengths 0–10) against the single-index version.

### 5. Merge Sorted Array
- **`mergeSortedArrays(nums1, n, nums2, m)`:** `n` is the number of real values in `nums1` and `m` is `nums2.size()`. Note that LeetCode's signature uses the opposite names (`merge(nums1, m, nums2, n)`). Pointers `p1 = n - 1`, `p2 = m - 1` and `curr = n + m - 1` move backwards: the larger of `nums1[p1]` and `nums2[p2]` goes to `curr`. Then only the `p2` tail is drained. See [Merging in place from the back](#merging-in-place-from-the-back).
- The first version **didn't compile**: `swap` was called without `std::` (see [Unqualified `swap` and ADL](#unqualified-swap-and-adl)). It now has `using std::swap;`.
- It uses `swap` instead of assignment, so `nums2` comes back filled with the placeholder values (`{2, 5, 6}` → `{0, 0, 0}` on the LeetCode example). Assignment avoids that, and then `nums2` can be a `const vector<int>&`.
- Skipping the `p1` tail loop is correct: the leftover `nums1` elements are already in place.
- The `return;` at the end of the `void` function can go (also noted in Reverse String).
- Edge cases tested: `nums2` empty, `nums1` empty (only the tail loop runs), both empty, all of `nums2` smaller (`nums1` shifts right completely) or all larger (`nums1` never moves), interleaved values, all equal, duplicates across arrays, negatives with `0` placeholders, non-zero garbage in the placeholders, `nums2` longer than `nums1`. A random cross-check runs 5000 pairs (lengths 0–10, values −5..5, placeholders set to 999) against `std::merge`.
- Removing the `p2` tail loop fails 7 checks, and flipping the comparison fails 11, so the tests catch both bugs.

### 6. 3Sum
- **`threeSumTwoPointers`:** sort, then for each `i` (skipping repeats, stopping once `nums[i] > 0`) run converging pointers `l = i + 1`, `r = n - 1` on the rest. After a match, move both and skip repeats of `nums[l]`. See [Fix one element, two-pointer the rest](#fix-one-element-two-pointer-the-rest-3sum).
- **`threeSumHashed`:** sort and count every value in an `unordered_map`. The map only ever holds the elements **after `j`**: `nums[i]` is taken out for good, and each `nums[j]` is taken out as `j` moves forward and put back in one loop once the `j` loop is done. So `target = -(nums[i] + nums[j])` can only match a later element, and each triplet is found exactly once (`nums[i] <= nums[j] <= target`) with no extra check. The `--` comes before the repeat checks on purpose: a skipped element still has to leave the map.
- It's also O(n²), but it pays for hashing on every lookup and still needs the sort, so the two-pointer version is the one to give in an interview.
- The first version **didn't compile**: a missing `;` after `r--`, and `res.insert({...})` (a `vector` has no `insert` that takes just a value without a position, so it should be `push_back`).
- The lookup was `mp[target] > 0`, which inserts a `0` entry on every miss (see [`operator[]` on a map inserts missing keys](#operator-on-a-map-inserts-missing-keys)). It now uses `find`. It also now stops once `nums[i] > 0`.
- **A version that looks the same but is wrong:** an earlier draft put each `nums[j]` back right after using it (`mp[nums[j]]++` inside the `j` loop) and also put `nums[i]` back. Then the map holds values from before `j` too, so:
  - Each triplet is found once per order (`[-1, 0, 1]` came back 3 times). It needs an extra `target >= nums[j]` check.
  - The `continue`s skip the `++`, so the counts drift lower and triplets go missing: `[-2, 0, 0, 0]` returned `[]`. The checks have to come before the `--` (see [Take out, then put back](#take-out-then-put-back-count-maps)). The duplicates often hid this, because the missing triplet was found later in a different order.
  - The final version avoids both problems, because nothing goes back into the map until the whole `j` loop is done.
- Both versions take `vector<int>&` (LeetCode's signature) and sort it, so the caller's vector gets reordered. Take it by value if the caller's order matters.
- The harness sorts inside each triplet and then sorts the list of triplets, **without** removing anything. Order doesn't matter, but duplicates still count as a failure.
- Edge cases tested: empty, 1 and 2 elements, exactly 3 that do / don't sum to 0, all zeros (3 and 6 of them, `[0, 0, 0]` once), only two zeros, all positive, all negative, a value needed twice (`[-2, 1, 1]`) vs present only once, the LeetCode example, repeats in the first and in the middle/last positions, several answers sharing a first element, `[-2, 0, 0, 0]`, and unsorted input. A random cross-check runs 5000 arrays (length 0–12, values −5..5) against an O(n³) brute force.
- The put-back-each-`j` draft fails 8 of the 18 hand-written checks and the random cross-check (335 arrays with the wrong set, 2226 with duplicates), so the tests catch both of its bugs.

### 7. 4Sum
- **`fourSumHashed`:** the same idea as `threeSumHashed`, with one more loop. Sort, count every value, and fix `i < j < k` (each skipping repeats). The map only ever holds the elements **after `k`**: each index is taken out as its loop reaches it, and the elements after it are put back in one loop when that loop finishes. Look up `target - sum` with `find`. O(n³) time, O(n) for the map.
- The first version **overflowed**: `long sum = nums[i] + nums[j] + nums[k];` adds three `int`s, so `[1e9, 1e9, 1e9, 1e9]` with target `-294967296` overflowed at 3×10⁹. GCC wrapped it to −1294967296, so `target - sum` came out as exactly 10⁹ and the wrong quadruplet was returned. It passed on LeetCode, most likely because Clang can turn the overflowing add into a 64-bit one. See [Signed overflow](#signed-overflow-the-type-comes-from-the-operands). It now uses `(long long) nums[i] + nums[j] + nums[k]`.
- Cleanups:
  - The map is now `unordered_map<long long, int>`. The key stays 64-bit because the lookup value `target - sum` can be outside `int`'s range, and the count only needs an `int`.
  - `mp.find(...) != end && mp[...] > 0` (two lookups) is now one `find` whose iterator is reused.
  - The loop variable `for (long n : nums)` reused the name of `long n = nums.size();`. Indices are now `int`, and only the sum is 64-bit.
  - Removed the unused `using std::swap;` and `<utility>`.
- **`fourSumTwoPointers`:** sort, then `kSumHelper(4, nums, target, 0, n - 1, res, currentVals)`. Each level fixes `nums[i]` (skipping repeats) and recurses with `k - 1` and `target - nums[i]`, and `k == 2` is the converging two pointers. `target` is passed as `long long`, so the subtractions can't overflow. It returns early or `break`s when `nums[r] * k < target` or `nums[i] * k > target`. See [Fix one element, two-pointer the rest](#fix-one-element-two-pointer-the-rest-3sum). O(n³) time, O(k) recursion depth and stack of current values.
- Fixes to the first recursive version:
  - It **didn't compile**: `kSumHelper` was called before it was declared. It's now defined above `fourSumTwoPointers`.
  - The current values were a `std::list<int>`. They're now a `vector<int>` with `reserve(4)` (see [`vector` over `list`](#vector-over-list-the-default-container)).
  - The helper takes `const vector<int>& nums`, since it only reads it.
  - `(int) (nums.size() - 1)` became `int n = nums.size();` and `n - 1` (see [`size() - 1` on an empty container](#size---1-on-an-empty-container)).
  - The 2-element sum is now `long long`. `int` was safe only because LeetCode's values stay within ±10⁹.
  - It now stops early using the bounds above.
- **First attempt (an outer pair moving towards each other):** it moved `l`, `r` based on the single sum `nums[l] + nums[r] + nums[l + 1] + nums[r - 1]`. That's wrong: one sum with one middle pair says nothing about the other middle pairs, so moving `l` can discard a `nums[l]` that still pairs with a smaller `nums[r]`. It only tries O(n) outer pairs when O(n²) are needed. On `[-2, -1, 0, 2, 2, 3]` with target `2` it returned only `[-2, -1, 2, 3]` and missed `[-2, 0, 2, 2]`. It also summed in `int`.
- The harness works like the 3Sum one, with the brute force summing in `long long`. Edge cases tested: empty, 3 elements, exactly 4 that do / don't hit the target, all equal (4 and 6 copies), LeetCode example 1, a negative target, answers sharing the first element and answers sharing the last, a gap between the outer and middle pairs, `[-2, -1, 0, 2, 2, 3]` with target `2` (same first element, different last), and the 1e9 overflow case. A random cross-check runs 5000 arrays (length 0–10, values −5..5, target −6..6) against an O(n⁴) brute force.
- The outer-pair first attempt failed the same-first/different-last check, the overflow check, and 481 random arrays. Both current versions pass everything.
