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

## Discarding a side safely (Container With Most Water)
- Converging pointers only work if each move **provably throws away no answer**. Say why before writing the move.
- Container: `area(l, r) = min(h[l], h[r]) * (r - l)`. Suppose `h[l] <= h[r]`. Any other container that uses `l` with `r' < r` has a height of at most `h[l]` (the shorter side caps it) and a smaller width, so its area is less than the area just computed. So `l` can't be in a better answer than the current one, and `l++` is safe.
- Move the **shorter** side. Moving the taller one keeps the cap `h[l]` and only shrinks the width, so it can skip the best pair: on `[1, 8, 6, 2, 5, 4, 8, 3, 7]` it gives 8 instead of 49. On a tie, either side can move, because the argument applies to both.
- **Skipping more (constant factor):** after computing the area with `h = min(h[l], h[r])`, every line on either side with height `<= h` can be skipped, because any container using one has height `<= h` and a smaller width. `while (l < r && h[l] <= h) l++; while (l < r && h[r] <= h) r--;`
- The same "why can this side go" check is what was missing in the first 4Sum two-pointer attempt (see [7. 4Sum](#7-4sum)).

## Greedy pairing from both ends (Boats to Save People)
- Sort, then pair the **heaviest** remaining person with the **lightest**. If they fit together, both go (`l++`, `r--`). If not, the heaviest goes alone (`r--`). Either way that's one boat.
- **Why it's optimal (exchange argument):**
  - The heaviest person `r` needs a boat in every solution.
  - If even the lightest doesn't fit with them, nobody does, so `r` goes alone in every solution.
  - If the lightest fits with them: take any optimal solution where `r` isn't with `l`. Say `r` shares with `x` (or is alone) and `l` shares with `y` (or is alone). Swap `l` and `x`, so the boats become `{r, l}` and `{x, y}`. `{r, l}` fits by assumption. `{x, y}` fits because `y <= r` (`r` is the heaviest), so `x + y <= x + r <= limit`. Missing partners just leave someone alone. The boat count doesn't change, so pairing `r` with `l` is never worse.
- It's the same "say why this side can go" check as in [Discarding a side safely](#discarding-a-side-safely-container-with-most-water), here for a greedy choice instead of a search.
- `l <= r`, not `l < r`: when `l == r`, one person is left and still needs a boat. Both branches then end the loop after counting one boat.
- **Counting sort for small value ranges:** weights are at most `limit` (≤ 3·10⁴), so counting sort makes the sort O(n + limit) instead of O(n log n). See [Counting sort](../1-arrays_and_hashing/NOTES.md#counting-sort-and-bucket-sort-by-frequency). Size the counts by the bound in the input (`limit`), not a hardcoded constant, and make sure every value is within it, or `counts[v]` writes out of bounds.

## Water above a bar (Trapping Rain Water)
- The water above bar `i` is `min(maxLeft(i), maxRight(i)) - h[i]`, where both maxes **include** `i` itself, so the result is never negative. The answer is the sum over all bars. Every approach is a way to get those two maxes cheaply.
- **Prefix/suffix maxes:** one forward pass for the running max from the left, one backward pass for the running max from the right. O(n) time, O(n) space. The backward pass can keep its max in a variable and add up the water as it goes, so only one array is needed.
- **Two pointers, O(1) space:** keep `leftMax` (max of `h[0..l]`) and `rightMax` (max of `h[r..n-1]`). Process the side with the **smaller max**: if `leftMax <= rightMax`, the real right max of `l` is at least `rightMax >= leftMax`, so the water at `l` is exactly `leftMax - h[l]`. The left side doesn't need to know the real right max, only that it's at least as tall.
- The common variant compares the **bars** (`h[l] < h[r]`) instead of the maxes. It's also correct: a pointer only moves off a bar when the other side has a taller one, so the side with the shorter bar always has the smaller max. Comparing the maxes makes the proof one line, so it's easier to defend in an interview.
- It's the same "say why this side can go" check as in [Discarding a side safely](#discarding-a-side-safely-container-with-most-water). Here the reason is "this side's water is already fully determined".
- A third approach, the **monotonic stack**, fills the water in horizontal layers. It's covered with the stack topic.

## Same-direction pointers on sorted input (dedupe)
- On **sorted** input, equal values are next to each other, so "seen before" is just "equal to the last kept value". A write pointer `w` and a read pointer `r` both move forward: `if (nums[r] != nums[w - 1]) nums[w++] = nums[r];`. O(n) time, O(1) space, with no hash set (compare the hash-set version in [Arrays & Hashing #26](../1-arrays_and_hashing/NOTES.md#26-remove-duplicates-from-sorted-array)).
- **At most `k` copies** of each value (Remove Duplicates II has `k = 2`): start `w = k` and compare with `nums[w - k]` instead of `nums[w - 1]`. If `nums[r]` equals the value `k` slots back, there are already `k` copies kept.
- Move with assignment, not `swap`: the slots past `w` don't matter, so the extra writes are wasted (the same point as in [Merging in place from the back](#merging-in-place-from-the-back)).

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

## Rotating an array in place
- Reduce `k` first with `k %= n`, because rotating by `n` is a no-op and `k` can be larger than `n`. That needs `n > 0`: `k % 0` is UB (in practice the program crashes with SIGFPE).
- **Reversal:** for a right rotation by `k`, reverse the whole array, then reverse `[0, k)` and `[k, n)`. Reversing everything moves the last `k` elements to the front, but backwards. Reversing each part restores the order inside it. About `n` swaps, O(1) space, and every pass walks memory in order.
- A **left** rotation by `k` is a right rotation by `n - k`. Or reverse `[0, k)` and `[k, n)` first, then the whole array.
- **Cyclic replacements (juggling):** start at `i`, carry the value to `i + k`, take the value that was there on to `i + 2k`, and so on until you're back at `i`. There are `gcd(n, k)` cycles of `n / gcd(n, k)` elements each, so loop over starting points until `n` elements have moved in total. Exactly `n` writes, but each step jumps `k` ahead, which is cache-unfriendly on large arrays. The reversal is often faster in practice even though it does more writes (see [Access pattern beats operation count](#access-pattern-beats-operation-count-cache)).
- **`std::rotate(first, middle, last)`** (`<algorithm>`) makes `middle` the new first element. Right rotation by `k`: `middle = end() - k`. Left by `k`: `middle = begin() + k`. It returns an iterator to where the old first element ended up. O(n).
- `%` keeps the sign of the left operand in C++, so `-1 % 5 == -1`, not `4`. For a `k` that may be negative, normalize with `((k % n) + n) % n`.

## Access pattern beats operation count (cache)
- Memory is loaded in **cache lines** (64 bytes, or 16 `int`s). Walking an array in order uses every value in each line, and the hardware **prefetcher** spots the pattern and loads the next lines before you need them.
- **Jumping by a stride** (`i → i + k → i + 2k …`) uses one `int` per line once `k >= 16`, and the prefetcher can't predict wrapping jumps (`% n`). Once the array doesn't fit in cache, almost every access is a cache miss (roughly 100+ cycles to main memory, against a few cycles for an L1 hit).
- So **fewer operations isn't automatically faster.** In Rotate Array, cyclic replacements do exactly `n` writes but jump around. The reversal does about `2n` writes but always in order, and it usually wins on large arrays. It's the same reason `vector` beats `list` (see [`vector` over `list`](#vector-over-list-the-default-container)).
- Big-O ignores the constant factor, and cache behavior is often most of that constant. When two approaches have the same big-O, compare how they access memory. Measure if it matters.
- This comes up a lot in HFT interviews: be ready to explain *why* the in-order version is faster, not just that it is.

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
- `std::max(a, b)` / `std::min(a, b)` are templates that take **two arguments of the same type**. `max(long, long long)` doesn't compile: `long` and `long long` are different types even where both are 64 bits, so the template can't deduce a single `T`. Make both sides the same type, or name it: `std::max<long long>(a, b)`.
- `std::swap(a, b)` (`<utility>`) swaps two elements.
  - Whenever you write the three-line `temp` exchange (`int temp = x; x = y; y = temp;`), use `std::swap(x, y)` instead. It works between any two variables of the same type, not just array elements: in Rotate Array, `int temp = nums[curr]; nums[curr] = prev; prev = temp;` is `std::swap(prev, nums[curr])`.
  - It says what it does, can't get the order of the three assignments wrong, and is never slower (for `int` it compiles to the same code).
  - For `vector`, `string` and other containers it moves instead of copying (O(1)), so `std::swap(v1, v2)` is cheap. A hand-written `temp` copy of a vector is O(n).

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
| 8 | Rotate Array | [rotate_array.cpp](rotate_array.cpp) | `k %= n`, then reverse all, reverse `[0, k)`, reverse `[k, n)`. (Also cyclic replacements and `std::rotate`) | O(n) | O(1) |
| 9 | Container With Most Water | [max_area.cpp](max_area.cpp) | Converging pointers: record `min(h[l], h[r]) * (r - l)`, then move the shorter side | O(n) | O(1) |
| 10 | Boats to Save People | [boats_to_save_people.cpp](boats_to_save_people.cpp) | Sort, then pair heaviest with lightest if they fit, else heaviest alone; one boat per step | O(n log n), or O(n + limit) with counting sort | O(1), or O(limit) |
| 11 | Two Sum II (sorted input) | [2_integere_sum.cpp](2_integere_sum.cpp) | Converging pointers: sum too small → `l++`, too big → `r--`, return 1-indexed | O(n) | O(1) |
| 12 | Remove Duplicates from Sorted Array | [remove_duplicates.cpp](remove_duplicates.cpp) | Read pointer `r`, write pointer `l` on the last kept value; keep `nums[r]` when it differs | O(n) | O(1) |
| 13 | Trapping Rain Water | [trapping_rain_water.cpp](trapping_rain_water.cpp) | Water at `i` is `min(maxLeft, maxRight) - h[i]`. Prefix/suffix maxes, or two pointers moving the side with the shorter bar | O(n) | O(n) prefix arrays, O(1) two pointers |

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

### 8. Rotate Array
- **`rotateCyclic`:** cyclic replacements. For each start `i`, carry `prev` around the cycle `i → i + k → …` (mod `n`) until it's back at `i`. The outer loop stops once `count` reaches `n`, which happens after `gcd(n, k)` cycles. See [Rotating an array in place](#rotating-an-array-in-place).
- **`rotateByReversing`:** `k %= n`, then reverse all, reverse `[0, k)`, reverse `[k, n)`.
- **`rotateUsingSTLFunction`:** `std::rotate(begin, end - k, end)`, so `end - k` becomes the first element. That's a right rotation.
- All three now return early on `n == 0` and normalize a negative `k` with `k += n` after `k %= n`. After the `%`, a negative `k` is between `-n` and `0`, so one `+ n` is enough.
- Fixes from review:
  - **Empty input crashed all three:** `k % n` with `n == 0` divides by zero. Fixed with `if (n == 0) return;`.
  - **A negative `k` broke them:** `k % n` stays negative, so the cyclic version indexed `nums[-1]` and `begin() + k` went out of range. Fixed with `if (k < 0) k += n;`. LeetCode doesn't allow a negative `k`, but it's a left rotation.
  - The three `temp` lines in `rotateCyclic` became `swap(prev, nums[curr])` (see [Standard library helpers](#standard-library-helpers)). `prev` is the **value** being carried around the cycle.
  - **An intermediate attempt that was wrong:** carrying an *index* (`swap(nums[prevIdx], nums[curr])` with `prevIdx = curr` after each step). After the first swap, `nums[i + k]` already holds the right value, and the next swap pushes that same value on to `i + 2k`. LeetCode example 1 gave `[1, 5, 6, 7, 4, 2, 3]`. Swapping with the fixed start, `swap(nums[i], nums[curr])`, also works: `nums[i]` then acts as the carry slot.
  - All three now store `int n = nums.size();`, so the style is consistent.
  - **`rotateCyclic` returns early on `k == 0`.** Without it, every element is its own cycle of length 1: the `do-while` runs its body once (`curr = i`, a swap of equal values) and exits. That's `n` writes that change nothing. It's still correct and O(n), just wasted.
- **Performance:** cyclic does exactly `n` writes, but they're strided by `k`. The reversal makes about `2n` writes walking memory in order. For large arrays the reversal is usually the faster one (see [Access pattern beats operation count](#access-pattern-beats-operation-count-cache)), and it's the expected interview answer. Mention `std::rotate` as the built-in.
- Edge cases tested: both LeetCode examples, a single element, `k = 0`, `k = n`, `k > n`, `k` much larger than `n`, `k = n - 1`, two elements, `gcd(n, k) = 2` and `3` (several cycles, so the outer loop of the cyclic version runs more than once), half of an even `n`, and duplicates. A random cross-check runs 5000 arrays (length 1–20, `k` 0–50) against a brute force that copies element `i` to `(i + k) % n` in a new array. Also tested: empty input, a negative `k` (left rotation), and a negative `k` with `|k| > n`.

### 9. Container With Most Water
- **`maxAreaNaive`:** every pair `i < j`, O(n²). It's used as the reference in the random check.
- **`maxAreaTwoPointers`:** `l = 0`, `r = n - 1`. Record `h * (r - l)` with `h = min(h[l], h[r])`, then skip every line `<= h` on both sides (`while (l < r && h[l] <= h) l++;` and the same for `r`). The shorter side always has height `h`, so at least one pointer moves each iteration, and no separate "move the shorter side" step is needed. On a tie, both sides get skipped, which is safe. See [Discarding a side safely](#discarding-a-side-safely-container-with-most-water).
- Fixes from review:
  - **It didn't compile:** `max(min((long) …, (long) …) * (long) …, maxArea)` passed a `long` and a `long long` to `std::max` (see [Standard library helpers](#standard-library-helpers)). Both versions now compute `long long h = min(…)` and `h * (r - l)`, all in `long long`. That's the type to use anyway, because `long` is 32 bits on Windows (see [Signed overflow](#signed-overflow-the-type-comes-from-the-operands)).
  - The skip loops replaced the `if (h[l] < h[r]) l++; else r--;` step. Both versions pass every test.
- **Interview polish** (HFT interviewers notice these, and both are now applied):
  - Both functions take `const vector<int>& heights`, since they only read it.
  - The redundant `(long long) (r - l)` cast is gone. `h` is already `long long`, so in `h * (r - l)` the `int` on the right is promoted anyway. Knowing exactly which operand forces the widening is the point here (see [Signed overflow](#signed-overflow-the-type-comes-from-the-operands)).
- `int r = (int) heights.size() - 1;` casts **before** subtracting, so an empty input gives `-1` and the loop doesn't run. That's correct.
- LeetCode's limits (heights ≤ 10⁴, `n` ≤ 10⁵) keep the area ≤ 10⁹, which fits in `int`, but `long long` costs nothing and handles the `INT_MAX` test.
- Edge cases tested: both LeetCode examples, empty, a single line, all zeros, all equal, strictly increasing and strictly decreasing, tall ends, a tall middle pair, equal ends with taller lines inside, and an area above `INT_MAX` (`{2e9, 1, 1, 2e9}` → 6×10⁹). A random cross-check runs 5000 arrays (length 0–30, heights 0–10) against the naive version.
- Moving the taller side instead fails LeetCode example 1 (8 instead of 49) and 3 other checks. Moving `l` on a tie (`<=`) passes everything.

### 10. Boats to Save People
- **`numRescueBoats`:** `sort`, then `l = 0`, `r = n - 1` while `l <= r`. If `people[l] + people[r] > limit`, the heaviest goes alone (`r--`). Otherwise both go (`l++`, `r--`). Count one boat per step. See [Greedy pairing from both ends](#greedy-pairing-from-both-ends-boats-to-save-people).
- **`numRescueBoatCountingSort`:** the same loop after `countSort(people, limit)`. Every weight is `<= limit`, so `limit + 1` buckets are enough.
- Fixes from review:
  - **It didn't compile:** `countSort` was called before it was declared (the same slip as `kSumHelper` in [4Sum](#7-4sum)). It's now declared at the top of the file.
  - `countSort(people, 30000)` hardcoded LeetCode's bound. It's now `countSort(people, limit)`, so the bound comes from the input and the array is smaller when `limit` is small. A weight above the bucket size would write past the end of `counts` (UB). That's ruled out only by the "weight <= limit" constraint.
  - The `long long boats` counter was returned as `int`. Both functions now return `long long`, so the types match. `int` would also be enough (at most `n` ≤ 5·10⁴ boats).
- **Interview polish:**
  - The two-pointer loop is copied into both functions. One helper taking the sorted array would make the versions differ only in how they sort.
  - `long long totalWeight` isn't needed: two weights ≤ 3·10⁴ sum to ≤ 6·10⁴. It isn't wrong, but be ready to say why `int` fits (the habit is to *check* the bound, not to widen everything).
  - The counting sort parameter `bucketSize` is really the maximum value.
- Counting sort is O(n + limit) time and O(limit) extra space, against O(n log n) and O(1) (apart from `std::sort`'s stack) for the other. At LeetCode's sizes both are fast. Mention it as the follow-up when the value range is small.
- Optional: with the counts you don't need to rebuild the sorted array. Run the two pointers over the weight values `1..limit` with the counts directly, which saves the O(n) write-back.
- Edge cases tested: the three LeetCode examples, empty, a single person, pairs that fit exactly at the limit, everyone over half the limit (no pairs), all light (still at most two per boat), an odd number of light people, the heaviest equal to the limit, heaviest-with-lightest pairing (`{1, 2, 2, 3}`, limit `4` → 2), and two people at the maximum weight 30000 (the top bucket). A random cross-check runs 5000 groups (0–12 people, limit 1–10) against a subset DP brute force: the lowest-numbered person still waiting goes alone or with any one other person who fits.

### 11. Two Sum II (sorted input)
- **`twoSum(v, t)`:** `l = 0`, `r = n - 1`. If `v[l] + v[r] < t`, `l++`. If it equals `t`, return `{l + 1, r + 1}` (LeetCode is 1-indexed). Otherwise `r--`. It returns `{-1, -1}` if there's no pair, which LeetCode rules out (exactly one answer). Why each move is safe: see [Fix one element, two-pointer the rest](#fix-one-element-two-pointer-the-rest-3sum).
- `int r = (int) v.size() - 1;` casts before subtracting, so empty input gives `-1` and the loop doesn't run. Correct.
- **Interview polish:**
  - Take `const vector<int>&`: the function only reads `v`. With `vector<int>&`, a braced list or a temporary can't be passed, so the harness needs a small `run` wrapper that copies into a local first (see [Copy or reference for a string parameter](#copy-or-reference-for-a-string-parameter), same rule).
  - `v[l] + v[r]` is computed twice. Store `int sum = v[l] + v[r];` once. LeetCode's values are within ±1000, so `int` fits. Without a bound, sum in `long long` (see [Signed overflow](#signed-overflow-the-type-comes-from-the-operands)).
  - `return vector({l + 1, r + 1});` can be `return {l + 1, r + 1};`, since the return type is already known.
- Edge cases tested (all pass): the three LeetCode examples, the pair at both ends, at the end, at the start (negatives), equal values (`{0, 0, 3, 4}`, target `0`), no pair, a target that needs one element twice (`{3, 4, 5}`, target `6` → no pair), empty, and a single element. A random cross-check runs 5000 sorted arrays (length 0–15, values −10..10). Random arrays can have several valid pairs, so it checks that the returned indices are a valid pair (1-indexed, `i < j`, right sum), or that no pair exists when it returns `{-1, -1}`.

### 12. Remove Duplicates from Sorted Array
- **`removeDuplicates`:** `l` is the last kept value and `r` reads ahead. When `nums[l] != nums[r]`, `l++` and the new value goes to `nums[l]`. Returns `l + 1`. Empty input returns `0` first. This is the O(1)-space version suggested in the [Arrays & Hashing notes](../1-arrays_and_hashing/NOTES.md#26-remove-duplicates-from-sorted-array), with no hash set. See [Same-direction pointers on sorted input](#same-direction-pointers-on-sorted-input-dedupe).
- **Interview polish:**
  - `swap(nums[l], nums[r])` can be `nums[l] = nums[r]`. Only the first `l + 1` slots matter, so the swap's extra writes are wasted. Then `using std::swap;` and `<utility>` can go.
  - `r < nums.size()` compares `int` with `size_t` (`-Wsign-compare`). Store `int n = nums.size();` once (see [`size() - 1` on an empty container](#size---1-on-an-empty-container)).
  - `nums.size() == 0` reads better as `nums.empty()`.
- Edge cases tested: empty, single element, two equal, two different, all the same, all unique, both LeetCode examples, duplicates at the start and at the end, runs of different lengths, negatives, and `INT_MIN` / `INT_MAX`. A random cross-check runs 5000 sorted arrays (length 0–20, values −5..5) against `std::unique`. The harness compares the first `k` elements, so a wrong `k` and a wrong prefix both fail.

### 13. Trapping Rain Water
- **`trapPrefixArrays`:** the forward pass stores the running max from the left in `maxGrid`. The backward pass keeps the running max from the right in `maxUntilNow`, sets `maxGrid[i]` to the smaller of the two, and adds `maxGrid[i] - heights[i]`. O(n) time, O(n) space. See [Water above a bar](#water-above-a-bar-trapping-rain-water).
- **`trapTwoPointers`:** while `l <= r`, update `leftMax` with `heights[l]` and `rightMax` with `heights[r]`. If `heights[l] < heights[r]`, add `min(leftMax, rightMax) - heights[l]` and `l++`. Otherwise do the same for `r` and `r--`. O(n) time, O(1) space.
- Both are correct, and the harness confirms it. Empty input works for both (`n = 0`, so neither pass runs; `r = -1`, so the `while` doesn't run).
- **Why `min(leftMax, rightMax)` is safe, and also not needed:** when `heights[l] < heights[r]`, `leftMax <= rightMax` always holds. `leftMax` came from some earlier bar `l'`, and `l'` was passed only because a bar on the right at the time was **taller** than it, so `rightMax > h[l'] = leftMax`. The `else` side works the same way (on a tie, `r` moves, so it's `>=`). The `min` therefore always picks the moving side's own max, and `leftMax - heights[l]` alone is enough. Keeping the `min` isn't wrong, but be ready to explain why the moving side's max is enough. Or compare `leftMax <= rightMax` instead of the bars, which makes the proof one line.
- **`l <= r` vs `l < r`:** both are correct. With `<=`, the bar where the pointers meet is processed once, and both maxes already include it, so it adds `>= 0`. With `<`, that bar is skipped. It's the tallest bar overall, because a pointer never leaves the tallest bar it has seen, so it holds no water anyway.
- **Interview polish:**
  - In `trapPrefixArrays`, filling `maxGrid` with `INT_MAX` and taking `min` in the **first** pass is redundant: `min(x, INT_MAX)` is just `x`. `vector<int> maxGrid(n);` with `maxGrid[i] = maxUntilNow;` says the same thing, and then `<climits>` can go.
  - Overflow: LeetCode allows `n` ≤ 2·10⁴ and heights ≤ 10⁵, so the total water is below 2·10⁹, just under `INT_MAX` (≈ 2.147·10⁹). `int` fits, but only just. That's the bound to check out loud. With larger limits, sum in `long long` (see [Signed overflow](#signed-overflow-the-type-comes-from-the-operands)).
- Edge cases tested (all pass): both LeetCode examples, empty, a single bar, two bars, all zeros, all equal, strictly increasing and strictly decreasing (no water), equal walls (`{2, 1, 2}`), unequal walls (`{5, 0, 3}`, capped by the shorter one), a flat pool, a valley, two pools between equal walls (`{3, 0, 3, 0, 3}`, so the tie branch runs), a bump inside a pool (`{5, 1, 3, 1, 5}`), and the tallest bar in the middle. A random cross-check runs 5000 arrays (length 0–20, heights 0–6) against an O(n²) version that finds both maxes for each bar.
