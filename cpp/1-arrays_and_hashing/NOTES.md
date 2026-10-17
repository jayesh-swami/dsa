# Arrays & Hashing — Notes

The concepts come first, for a quick revision. The problem-by-problem notes are at the end, for when you want more detail.

# Concepts

## Hashing patterns
| Need | Tool |
|------|------|
| "Have I seen this before?" | `unordered_set` |
| "How many times?" / "Where did I see it?" | `unordered_map<T, count/index>` |
| "Group things that are equivalent" | `unordered_map<canonical_key, vector<T>>` |

- The trick is usually choosing a **canonical key** (sorted string, char counts, complement `target - x`).
- `map[key]++` works because `operator[]` default-inserts `0` for a missing key. Note that `operator[]` **inserts** — use `contains`/`find` when you only want to check.
- `contains()` is C++20; older code uses `find(x) != end()` or `count(x)`.
- `set.insert(x)` returns `pair<iterator, bool>`. `.second` is `false` when `x` was already there, so `if (!s.insert(x).second)` checks for a duplicate and inserts in one lookup.

## Sequence starts (longest consecutive run)
- Put everything in a hash set. A number `x` **starts** a run only if `x - 1` is not in the set. Count upwards only from those starts.
- Every number is visited by at most one run, so the total work is O(n). Counting from every element instead is O(n²) on input like `1..n`.
- Iterate over the **set**, not the input, so duplicates don't start the same run again.

## Grid boxes (Sudoku indexing)
- For a `k × k` box grid (`k = 3` for 9×9, `k = √N` in general), box `b` and cell `j` within it map to `row = (b / k) * k + j / k`, `col = (b % k) * k + j % k`.
- With that, one loop `i = 0..N-1` can check row `i`, column `i` and box `i` together, reusing one set and calling `clear()` between them.
- Alternative: one pass over the board with `N` sets per rows, columns and boxes, where cell `(r, c)` belongs to box `(r / k) * k + c / k`.

## Boyer-Moore Voting Algorithm
- Keep a `candidate` and a `count`. Same element as candidate → `count++`; different → `count--`. When `count` hits 0, the current element becomes the new candidate.
- Intuition: every non-majority element can "cancel" at most one majority vote. Since the majority appears more than `n/2` times, it's the only one that can survive.
- O(n) time, **O(1) space** (vs O(n) space for the hash map counting approach).
- **Catch:** it assumes a majority exists. If that's not guaranteed, do a second pass to verify the candidate's count is `> n/2`.

- **Generalisation (`> n/k`):** at most `k - 1` values can appear more than `n/k` times, so keep `k - 1` candidate/count pairs. A new value that matches no candidate and finds no empty slot decrements **all** counts. For `n/3` that's two candidates.
- With more than one candidate the **verification pass is mandatory**: the candidates are only "possible" answers, e.g. in `[1, 2, 3]` something survives even though nothing is above `n/3`.
- **Pitfall:** never let the two candidates hold the same value. If both start at the same sentinel (e.g. `-1`) and one never gets replaced, a real `-1` in the input is counted for both and reported twice. Count with `if / else if` in the verification pass, or check `cd1 != cd2` before adding the second one.

## `std::move` (from `<utility>`)
- `std::move` doesn't move anything by itself — it casts to an rvalue so the **move constructor/assignment** is chosen.
- For types that own heap memory (`string`, `vector`), moving transfers the internal buffer pointer: **O(1)** instead of an **O(len)** copy. This is similar to how Java passes object references around.
- For trivial types (`int`, `char`) a move is just a copy.
- The moved-from object is left valid but unspecified (usually empty) — don't rely on its contents afterwards.
- Example (Group Anagrams): `groupedAnagrams[move(sc)]` moves the sorted temp copy into the map key, and `ans.push_back(move(value))` moves each group out of the map instead of copying it.

## Two pointers on an array (in-place)
- A "write" pointer trails a "read" pointer; copy only what you want to keep. Gives O(1) extra space for filter/remove/dedupe-style problems.

## Designing a hash table (collision resolution)
- Core: `idx = hash(key) % TABLE_SIZE` into a fixed array of buckets. A **prime** table size spreads keys more evenly; pick it so the **load factor** (`elements / buckets`) stays low.
- **Negative keys:** in C++ `%` keeps the sign of the dividend (`-3 % 7 == -3`), so normalise with `h < 0 ? h + TABLE_SIZE : h`.
- **Separate chaining:** each bucket is a `list` of entries. Add/find/remove scan only that bucket. Simple, deletes are trivial (`list::erase`), and it degrades gracefully as the load factor grows.
- **Open addressing (linear probing):** one flat array; on a collision, try `(h + i) % TABLE_SIZE` for `i = 0, 1, 2, …`.
  - Each slot needs a status: `EMPTY`, `EXISTS`, `DELETED`.
  - **Tombstones:** removal marks a slot `DELETED` instead of `EMPTY`. Otherwise a later lookup would stop at the hole and miss keys that probed past it.
  - Lookup stops at `EMPTY` and skips over `DELETED`. Insert can reuse the first non-`EXISTS` slot, but only after confirming the key isn't already present.
  - Downsides: clustering, and the table fills up (it needs a capacity check or a resize). Quadratic probing (`h + i²`) reduces clustering.
- Other strategies (cuckoo hashing, etc.) are listed in the further readings notes.

## Kadane's Algorithm (maximum subarray sum)
- Track `sumEndingAtK`, the best sum of a subarray that **ends at** index `k`: `sumEndingAtK = max(nums[k], sumEndingAtK + nums[k])`. Either extend the previous subarray or start fresh at `k`.
- The answer is the max of `sumEndingAtK` over all `k`. O(n) time, O(1) space, vs O(n²) for checking every subarray.
- Initialise with the first element, or with `INT_MIN / 2`. Plain `INT_MIN` overflows on `sumEndingAtK + nums[k]` when `nums[k]` is negative.
- With all-negative input, the answer is the largest single element (empty subarrays not allowed).

## Sorting algorithms
| Algorithm | Best | Average | Worst | Extra space | Stable |
|-----------|------|---------|-------|-------------|--------|
| Bubble sort (with early exit) | O(n) | O(n²) | O(n²) | O(1) | Yes |
| Merge sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes |
| Quick sort (random pivot) | O(n log n) | O(n log n) | O(n²) | O(log n) stack | No |
| `std::sort` (introsort) | O(n log n) | O(n log n) | O(n log n) | O(log n) | No (`std::stable_sort` is) |

- **Bubble sort:** swap adjacent out-of-order pairs. After pass `i`, the largest `i + 1` elements are in their final place, so the inner loop can stop at `n - 1 - i`. If a pass makes no swaps, the array is sorted → return early (this is what gives the O(n) best case).
- **Merge sort:** split at `mid`, sort both halves recursively, then **merge** two sorted halves with two pointers into a temp buffer and copy it back. Taking from the left half on ties (`<=`) keeps it **stable**. Its runtime doesn't depend on the input order.
- **Quick sort:** pick a pivot and **partition** so that smaller elements go left and the rest go right. The pivot is then at its final index, so recurse on each side.
  - **Lomuto partition:** move the pivot to `end`, keep `i` as the boundary of the "< pivot" region, scan `j` and swap smaller elements to `i++`, then swap the pivot into `i`.
  - A **random pivot** avoids the O(n²) worst case on already sorted input. It does **not** help with many duplicates. With a strict `<`, equal elements all land on one side, so an all-equal array is still O(n²). The fix is a 3-way (Dutch national flag) partition or Hoare partition.
- **Bounds conventions:** decide whether `end` is inclusive or exclusive and stick to it. Here merge sort uses half-open `[start, end)` and quick sort uses closed `[start, end]`.
- **`std::uniform_int_distribution<int>(a, b)`** is **inclusive** on both ends, `[a, b]`. Use a fixed-seed `std::mt19937` so runs are reproducible.
- **Benchmarking:** time with `std::chrono::steady_clock` (monotonic) and check the result with `std::is_sorted`. Use `ios::sync_with_stdio(false); cin.tie(nullptr);` to read big inputs quickly.
- Measured on 50,000 random ints (`-O2`):

  | | Random input | 50,000 equal values |
  |---|---|---|
  | Bubble sort | ~0.81 s | — |
  | Merge sort | ~0.004 s | ~0.0015 s |
  | Quick sort (Lomuto, random pivot) | ~0.0025 s | **~0.25 s** (O(n²) on duplicates) |
  | `std::sort` | ~0.0018 s | — |

## Counting sort and bucket sort by frequency
- **Counting sort:** when there are only a few distinct values, count each one and then overwrite the array value by value. O(n + k) for `k` distinct values in a known small range, with no comparisons.
- **Unknown or sparse values:** count with an `unordered_map`, copy the `(value, count)` pairs into a vector and sort only those. O(n + k log k), so it's close to O(n) while `k ≪ n`. As `k → n` it is just a slower comparison sort (hashing every element, then sorting n pairs).
- **Dutch national flag (3 values):** one pass and O(1) space with three pointers `low`, `mid` and `high`. `0` → swap to `low++` and `mid++`; `1` → `mid++`; `2` → swap to `high--` and **don't** advance `mid`, because the swapped-in value hasn't been checked yet. It's the same 3-way partition that fixes quick sort on duplicates.
- **Bucket sort by frequency:** a frequency is always in `[1, n]`, so `bucket[f]` can hold the values seen `f` times. Walking from `f = n` down gives the most frequent values first, in O(n) and with no sorting.

## Top-k patterns
| Approach | Time | Notes |
|----------|------|-------|
| Count, then sort all `(count, value)` pairs | O(n + u log u) | Simplest. `u` = number of unique values |
| Min-heap of size `k` | O(n log k) | `priority_queue` with `greater<>`; pop once the size goes above `k` |
| `nth_element` / `partial_sort` | O(n + u) avg / O(n + u log k) | Only the top `k` needs to be in order, not everything |
| Bucket sort by frequency | **O(n)** | Counts are bounded by `n` |

- `sort(v.rbegin(), v.rend())` sorts in **descending** order. Pairs compare by `.first` first, so store them as `(count, value)`.

## Length-prefix encoding (serialising a list of strings)
- Write each string as `len#str`. The decoder reads digits up to `#`, then takes exactly `len` characters. Because it never looks for a delimiter inside the payload, the strings can contain `#`, digits or anything else.
- A plain delimiter (e.g. joining with `,`) breaks as soon as a string contains that delimiter, unless you add escaping.
- Empty strings encode as `0#`, and an empty list encodes as `""`, so both round-trip.
- O(total length) for both directions.

## 2D prefix sums (summed-area table)
- `P[i][j]` = sum of the rectangle from `(0, 0)` to `(i, j)`. Build it in one pass by inclusion-exclusion: `P[i][j] = P[i-1][j] + P[i][j-1] - P[i-1][j-1] + a[i][j]` (the top-left block is counted twice, so subtract it once).
- Any rectangle `(r1, c1)`–`(r2, c2)` is then `P[r2][c2] - P[r1-1][c2] - P[r2][c1-1] + P[r1-1][c1-1]`. O(n·m) to build, **O(1)** per query.
- **Padding:** make `P` size `(n+1) × (m+1)` with a zero first row and column, and shift indices by one. That removes every `< 0` bounds check.
- The 1D version is the same idea: `sum(l..r) = P[r+1] - P[l]`.

## Prefix and suffix products (everything except `i`)
- "Combine everything except index `i`" = (combine of everything **left** of `i`) ⊕ (combine of everything **right** of `i`). Build a left-to-right prefix array and a right-to-left suffix array, both starting at the identity (`1` for products), each shifted by one so index `i` excludes itself.
- **Why not divide?** `total / nums[i]` breaks on zeros (one zero → only that index is non-zero; two or more → all zeros) and the problem forbids division anyway. Prefix/suffix handles zeros with no special cases.
- **O(1) extra space:** write the prefix products straight into the output array, then sweep right to left with a single running suffix variable and multiply it in. The output array doesn't count as extra space.

## Prefix sum + hash map (count subarrays with sum `k`)
- `sum(i+1..j) = prefix[j] - prefix[i]`. So a subarray ending at `j` sums to `k` exactly when some earlier prefix equals `prefix[j] - k`.
- Sweep once, keeping `count[prefixSum]` for every prefix seen so far. At each step add `count[currSum - k]` to the answer, **then** record `currSum`. Recording first would count the empty subarray when `k == 0`.
- Seed with `count[0] = 1` (the empty prefix) so subarrays that start at index 0 are counted.
- Works with **negatives and zeros**, which is exactly where a sliding window breaks (the window sum is no longer monotonic as it grows).
- Same trick, different map value: store the **first index** of each prefix instead of a count to get the *longest* subarray with sum `k`. Use `prefix % m` as the key for "sum divisible by `m`".
- `map[x]` on a missing key inserts it. Use `find` when you only want to read, so the map doesn't fill up with zero entries.

## Monotonic stack (nearest smaller to the left)
- Keep a stack whose values stay sorted (non-decreasing from bottom to top). For each new element, **pop everything bigger**, read the top (the nearest element to the left that is `<=` the current one), then push the current element.
- Each index is pushed and popped at most once, so the whole sweep is O(n), even though there's a `while` inside the `for`.
- Store `(value, index)` pairs when you need to know *where* the nearest smaller element was, not just its value.
- Flip the comparison for "nearest greater", or sweep right to left for "nearest to the right".

## Greedy: sum of positive differences (unlimited transactions)
- When you can trade as often as you like, any trade `buy a → sell b` equals the sum of the daily steps `a→a+1, …, b-1→b`. So the best profit is the sum of every positive `prices[i] - prices[i-1]`.
- Check whether "one big move" can be broken into small independent moves. If it can, a greedy that takes every small gain is optimal.

## Using the array as its own hash set (sign marking)
- If the answers that matter are in `1..n` (`n = nums.size()`), index `v - 1` can be the "seen" flag for value `v`. Make `nums[v - 1]` negative to mark `v` present. O(1) extra space, but **it destroys the input**.
- First clear out values that would confuse the marking: anything `<= 0` becomes something out of range (like `n + 1`). A `0` can't hold a negative mark, and existing negatives would look like marks.
- Read values with `abs()`, because an earlier step may have already flipped that slot negative.
- Only flip when the slot is still positive, so a duplicate doesn't flip it back.
- Related: **cyclic sort** puts each `v` in `1..n` at index `v - 1` by swapping. Same O(n) time and O(1) space, and the input keeps its values (just reordered).

## Cyclic sort (place each value at index `v - 1`)
- For each `i`, keep swapping `nums[i]` into slot `nums[i] - 1` **while** it's in `1..n` and that slot doesn't already hold it. Then the first `i` with `nums[i] != i + 1` is a missing value.
- The guard `nums[nums[i] - 1] != nums[i]` matters twice: it stops duplicates (`{1, 1}`) from swapping forever, and it already covers `nums[i] == i + 1`, so a separate check for that is redundant.
- A `while` inside a `for`, but O(n): every swap puts one value in its final slot, so there are at most `n` swaps in total.
- Compared with sign marking: no `abs`, no replacement value, and the values survive (just reordered). It still changes the input order.
- The same pattern solves Missing Number, Find All Duplicates and Find All Missing Numbers.

## Memory ownership in C++
- Returning `vector` → RAII, no manual cleanup.
- Output buffer parameter → caller owns memory.
- Returning `new[]` pointer → caller must `delete[]` (prefer `std::unique_ptr<int[]>` or `vector` to avoid leaks).
- `reserve(n)` on a vector when the final size is known avoids reallocations during `push_back`.

---

# Problems

| # | Problem | File | Approach | Time | Space |
|---|---------|------|----------|------|-------|
| 1 | Concatenation of Array | [concatenation_of_array.cpp](concatenation_of_array.cpp) | Index with `i % n` | O(n) | O(n) |
| 2 | Contains Duplicate | [contains_duplicates.cpp](contains_duplicates.cpp) | Hash set, early exit | O(n) | O(n) |
| 3 | Valid Anagram | [is_anagram.cpp](is_anagram.cpp) | Character frequency maps | O(n) | O(k) |
| 4 | Two Sum | [two_sum.cpp](two_sum.cpp) | One-pass hash map of complements | O(n) | O(n) |
| 5 | Longest Common Prefix | [longest_common_prefix.cpp](longest_common_prefix.cpp) | Vertical scan against first string | O(n·m) | O(1) |
| 6 | Group Anagrams | [group_anagrams.cpp](group_anagrams.cpp) | Sorted string as hash key + `std::move` | O(n·k log k) | O(n·k) |
| 7 | Remove Element | [remove_element.cpp](remove_element.cpp) | Two pointers (in-place overwrite) | O(n) | O(1) |
| 8 | Majority Element | [majority_element.cpp](majority_element.cpp) | Hash map count **and** Boyer-Moore voting | O(n) | O(n) / **O(1)** |
| 9 | Design HashSet | [design_hashset.cpp](design_hashset.cpp) | Separate chaining **and** linear probing with tombstones | O(1) avg | O(TABLE_SIZE + n) |
| 10 | Design HashMap | [design_hashmap.cpp](design_hashmap.cpp) | Separate chaining with `list<pair<key, value>>` | O(1) avg | O(TABLE_SIZE + n) |
| 11 | Maximum Subarray Sum | [max_subarray_sum.cpp](max_subarray_sum.cpp) | Brute force over all start points **and** Kadane's | O(n²) / **O(n)** | O(1) |
| 12 | Sorting Algorithms | [sorting_algos.cpp](sorting_algos.cpp) | Bubble, merge, and quick sort (random pivot) benchmarked against `std::sort` | O(n²) / O(n log n) | O(1) / O(n) / O(log n) |
| 13 | Sort Colors | [sort_colors.cpp](sort_colors.cpp) | Counting sort for 3 values **and** a hash map plus sorting the distinct values for any `k` | O(n) / O(n + k log k) | O(1) / O(k) |
| 14 | Top K Frequent Elements | [top_k_frequent_elements.cpp](top_k_frequent_elements.cpp) | Hash map count, then sort pairs **and** bucket sort by frequency | O(n + u log u) / **O(n)** | O(n) |
| 15 | Encode and Decode Strings | [encode_decode_string.cpp](encode_decode_string.cpp) | Length prefix `len#str` | O(L) | O(L) |
| 16 | Range Sum Query 2D – Immutable | [range_sum_2d_query.cpp](range_sum_2d_query.cpp) | 2D prefix sums, with a bounds-checked helper **and** a zero-padded matrix | O(n·m) build, O(1) query | O(n·m) |
| 17 | Product of Array Except Self | [product_of_array_except_self.cpp](product_of_array_except_self.cpp) | Prefix and suffix product arrays **and** output array plus a running suffix | O(n) | O(n) / **O(1)** extra |
| 18 | Valid Sudoku | [valid_sudoku.cpp](valid_sudoku.cpp) | Hash set per row/column/box with box index math, for 9×9 **and** any N×N | O(N²) | O(N) |
| 19 | Longest Consecutive Sequence | [longest_consecutive_seq.cpp](longest_consecutive_seq.cpp) | Hash set, count only from run starts (`n - 1` absent) | O(n) | O(n) |
| 20 | Best Time to Buy and Sell Stock II | [best_time_to_buy_and_sell_stock_2.cpp](best_time_to_buy_and_sell_stock_2.cpp) | DP over every buy day, DP with a monotonic stack **and** greedy sum of upward moves | O(n²) / O(n) / **O(n)** | O(n) / O(n) / **O(1)** |
| 21 | Majority Element II | [majority_element_2.cpp](majority_element_2.cpp) | Hash map count with an `INT_MIN` "already added" marker **and** Boyer-Moore with two candidates | O(n) | O(n) / **O(1)** |
| 22 | Subarray Sum Equals K | [subarray_sum_equal_k.cpp](subarray_sum_equal_k.cpp) | Prefix sum + hash map of prefix counts, seeded with `{0: 1}` | O(n) | O(n) |
| 23 | First Missing Positive | [first_missing_positive.cpp](first_missing_positive.cpp) | `vector<bool>` of size `n + 1` **and** the input array as a hash set using sign marking **and** cyclic sort | O(n) | O(n) / **O(1)** / **O(1)** |

`k` = alphabet size or string length (#13: number of distinct values), `m` = length of shortest string (#16: number of columns), `u` = number of unique values, `L` = total length of all strings, `N` = side length of the Sudoku board.

### 1. Concatenation of Array
- Build `ans` of size `2n` with `ans[i] = nums[i % n]`. One loop, no need to copy twice.
- Three versions written to compare memory ownership styles (see [Memory ownership in C++](#memory-ownership-in-c)): `vector` return, caller-provided output buffer, and `new int[2n]` that the caller must `delete[]`.

### 2. Contains Duplicate
- Walk the array, insert into an `unordered_set`; if it's already there → duplicate.
- Check-then-insert gives an **early exit** on the first duplicate.
- Edge cases tested: empty, single element, negatives, `INT_MIN`/`INT_MAX`.

### 3. Valid Anagram
- Different lengths → can't be anagrams (cheap early return).
- Count characters of both strings in one loop, then compare the maps.
- Possible improvement: for lowercase-only input, an `int count[26]` (increment for `s`, decrement for `t`, check all zero) is faster and O(1) space.

### 4. Two Sum
- For each `nums[i]`, look up `target - nums[i]` in a map of `value → index` seen **so far**.
- Check **before** inserting the current number — this prevents using the same element twice and correctly handles duplicates (e.g. `{2, 5, 2}`, target `4` → `{0, 2}`).
- Return `{}` when no pair exists.

### 5. Longest Common Prefix
- Use the first string as the reference; for each index `i`, compare `first[i]` with every other string.
- Stop as soon as a string is too short (`i >= strs[j].size()`) or a character mismatches → return `first.substr(0, i)`.
- If the loop finishes, the whole first string is the prefix.
- Guard the empty-input case before calling `strs.front()`.

### 6. Group Anagrams
- Sort each string's characters → all anagrams map to the same key. Use `unordered_map<string, vector<string>>`.
- Alternative to explore: a key built from **character counts** (e.g. 26 counts), which avoids the `k log k` sort → O(n·k).
- Uses `std::move` for the map key and when moving groups into the answer (see [`std::move`](#stdmove-from-utility)).

### 7. Remove Element
- Two pointers: `fptr` marks where the next kept element goes; copy every element that isn't `val` to `nums[fptr++]`.
- Returns the count of kept elements; only the first `fptr` slots matter. Order is preserved.

### 8. Majority Element
- **Hashing:** count occurrences; return as soon as a count exceeds `n / 2`. O(n) space. Returns `INT_MAX` as a sentinel if no majority.
- **Boyer-Moore Voting:** O(n) time, O(1) space (see [Boyer-Moore Voting Algorithm](#boyer-moore-voting-algorithm)).

### 9. Design HashSet
- **Chaining (`MyHashSet`):** `vector<list<int>>` of size 19997 (prime). `add` scans the bucket to avoid duplicates; `remove` erases via iterator. It doesn't normalise negative keys, which is fine for LeetCode's `0 ≤ key ≤ 10⁶`.
- **Linear probing (`MyHashSetLinearProbing`):** parallel `hash` / `hashStatus` arrays and a shared `find()` helper. `remove` leaves a `DELETED` tombstone. `add` reuses the first non-`EXISTS` slot after `find` confirms the key is absent. `currentSize` guards against a full table.
- See [Designing a hash table](#designing-a-hash-table-collision-resolution).

### 10. Design HashMap
- Same chaining design as the HashSet, but buckets store `pair<int, int>`. `add` on an existing key **updates** the value in place (iterate with `auto&` so the update sticks).
- `get` on a missing key returns `INT_MAX` as a sentinel (LeetCode's version expects `-1`).
- Negative keys are normalised in `hash()`.

### 11. Maximum Subarray Sum
- **Naive:** for each start `i`, extend `j` and keep a running sum. O(n²), no O(n³) inner re-summing.
- **Kadane's:** extend or restart at each element, and track the best so far (see [Kadane's Algorithm](#kadanes-algorithm-maximum-subarray-sum)).
- Edge cases tested: zeros, the whole array as the answer, crossing a negative, all negatives.

### 12. Sorting Algorithms
- **`bubbleSort`:** a `swaps` counter per pass gives the early exit. The inner loop always goes to `n - 1` (it could stop at `n - 1 - i`).
- **`mergeSort(nums, start, end)`:** half-open range, so call it as `mergeSort(a, 0, a.size())`. The merge builds a `merged` vector and copies it back into `nums[start..end)`.
- **`quickSort(nums, start, end)`:** closed range, so call it as `quickSort(a, 0, a.size() - 1)`. `partitionQuickSort` picks a random pivot with `randomBetween` (inclusive `[start, end]`, which is correct for the closed range) and then does a Lomuto partition.
- `main` sorts a small hand-written array, then reads `n` numbers from stdin and times the sort. It prints `sort failure!` if any adjacent pair is out of order.
- See [Sorting algorithms](#sorting-algorithms) for complexities, trade-offs, and timings.

### 13. Sort Colors
- **`sortColors`:** counting sort hardcoded for `0`, `1`, `2`. One pass counts them, then three `while` loops overwrite the array. It takes two passes, so the Dutch national flag version is the one-pass follow-up (see [Counting sort and bucket sort by frequency](#counting-sort-and-bucket-sort-by-frequency)).
- **`sortColorsN`:** a generalisation for any values. Count with `unordered_map`, sort the `(value, count)` pairs, then write each value out `count` times. O(n + k log k).
- `tests/gen_sort_colors.cpp` writes inputs with `n = 10⁶` and `k = 10, 10², …, 10⁶` distinct values (each value appears at least once, fixed seed). `main` times `sortColorsN`, counts the distinct values and checks `std::is_sorted`.
- Measured with `-O2`, `n = 10⁶`:

  | k | 10 | 10² | 10³ | 10⁴ | 10⁵ | 10⁶ |
  |---|---|---|---|---|---|---|
  | `sortColorsN` | ~0.005 s | ~0.006 s | ~0.007 s | ~0.009 s | ~0.020 s | ~0.25 s |

  Time stays almost flat while `k ≪ n`. At `k = n` it jumps about 12×, because the map gets a million entries (cache misses, rehashing) and the `k log k` sort becomes a full sort.

### 14. Top K Frequent Elements
- **`topKFrequent`:** count into `unordered_map`, flip the entries to `(count, value)` pairs, sort them descending with `rbegin()`/`rend()`, and take the first `k`.
- **`topKFrequentBucket`:** `bucket` has `n + 1` slots indexed by count. Walk from `f = n` down and stop once `k` values are collected. O(n) time and space.
- The answer order doesn't matter, so the test harness sorts both vectors before comparing them. Both versions run through the same tests using a function-pointer type alias (`using Fn = vector<int> (*)(vector<int>&, int)`).
- Edge cases tested: a single element, negatives, `k` equal to the number of unique values, and all-distinct frequencies.
- See [Top-k patterns](#top-k-patterns) for the heap and `nth_element` alternatives.

### 15. Encode and Decode Strings
- **`encode`:** append `to_string(s.size()) + '#' + s` for every string.
- **`decode`:** read characters up to `#` into `strLen`, `stoi` it, skip the `#`, then copy the next `len` characters. Repeat until the end of the input.
- Possible improvements: take the input as `const string&` instead of by value, and use `str.substr(i, len)` (or `find('#', i)`) instead of building strings one character at a time.
- See [Length-prefix encoding](#length-prefix-encoding-serialising-a-list-of-strings).

### 16. Range Sum Query 2D – Immutable
- **`NumMatrix`:** an `n × m` prefix matrix. `sumFromTopLeft(r, c)` returns `0` when `r < 0` or `c < 0`, so the build and `sumRegion` can use the formulas directly.
- **`NumMatrixOptimized`:** an `(n+1) × (m+1)` padded matrix, so there are no branches. `sumMatrix[i+1][j+1]` holds the sum up to `(i, j)`.
- Both constructors read `matrix[0]`, so an empty matrix would be out of bounds (LeetCode guarantees `n, m ≥ 1`).
- `main` checks both classes on the LeetCode example (expected `8 11 12`).
- See [2D prefix sums](#2d-prefix-sums-summed-area-table).

### 17. Product of Array Except Self
- **`productExceptSelf`:** `left[i]` = product of `nums[0..i-1]`, `right[i]` = product of `nums[i+1..n-1]` (both start at `1`), and `res[i] = left[i] * right[i]`. Three passes, O(n) extra space.
- **`productExceptSelfMemoryOptimized`:** fill `res` with the left products, then walk right to left keeping `productUntilNow` (the suffix product) and multiply it into `res[i]`. O(1) extra space.
- Both take `vector<int>&`, so the tests can't pass a brace list directly. A `checkBoth` helper takes the input by value and runs the same case through both versions.
- Edge cases tested: two elements, one zero, several zeros, a zero at either end, all negatives, all ones.
- `int` can overflow for large products. LeetCode guarantees every prefix/suffix product fits in 32 bits.
- See [Prefix and suffix products](#prefix-and-suffix-products-everything-except-i).

### 18. Valid Sudoku
- **`isSudokuValid`:** for each `i`, check row `i`, column `i` and box `i` with one `unordered_set<char>` that is cleared between them. Skip `'.'`, and return `false` as soon as `insert(...).second` is `false`.
- **`isSudokuValidN`:** the same loop for any `N × N` board, with `-1` for empty cells. `k = sqrt(N)`, and the board is rejected if `k * k != N`.
- It only checks that the filled cells don't repeat. It doesn't check that the board is solvable or that the values are in range.
- Edge cases tested: empty and fully solved boards, a duplicate in only a row, only a column or only a box, the bottom-right box, 4×4 and 1×1 boards, a 3×3 board (not a perfect square), and 9×9 through the NxN version.
- Possible improvement: a `bool seen[9]` (or a bitmask) instead of `unordered_set`, since the values are small.
- See [Grid boxes](#grid-boxes-sudoku-indexing).

### 19. Longest Consecutive Sequence
- **`longestConsecutive`:** insert everything into an `unordered_set`, collect the numbers whose `n - 1` is missing, then count up from each with `while (s.contains(i)) i++`. The run length is `i - n`.
- The `candidates` vector could be dropped by counting straight inside the set loop.
- Edge cases tested: empty, single, duplicates, all the same, negatives, crossing zero, no consecutive numbers, two equal runs, values near `±10⁹`.
- `i++` past `INT_MAX` would overflow if the input contained `INT_MAX`. LeetCode's range (`|x| ≤ 10⁹`) avoids this.
- See [Sequence starts](#sequence-starts-longest-consecutive-run).

### 20. Best Time to Buy and Sell Stock II
- **`maxProfit` (naive DP):** `profitUntilN[k]` = best profit using days `0..k-1`, padded so `profitUntilN[0] = 0`. For each sell day `i`, try every earlier buy day `j-1`: `profitUntilN[j] + prices[i] - prices[j-1]`. Also carry forward the best value so far for the case where you don't sell on day `i`. O(n²).
- **`maxProfitOptimized` (monotonic stack):** you only need to try buying on the nearest day to the left with price `<=` today. Days in between cost more than today. For an earlier day `j`, "buy at `j`, sell at `k`" is already counted in `profitUntilN[k+1]`, so buying at `k` is never worse. O(n) time and space.
- **Always update `maxPro` even on days you don't sell.** Without it, a day with nothing smaller to its left (an empty stack) drops the profit you already made.
- **`maxProfitGreedy`:** add up every positive day-to-day difference. O(n) time, O(1) space. This is the one to use, and the DP versions are good for checking it.
- The original version didn't compile: `pair` was used without `using std::pair` (and `<utility>`).
- Edge cases tested: empty, single day, strictly increasing/decreasing, all equal, plateaus, zigzag, a dip then a rise. A random cross-check runs 1000 arrays (length 0–50, values 0–20, so lots of ties) and compares the stack and greedy versions with the naive DP.
- See [Monotonic stack](#monotonic-stack-nearest-smaller-to-the-left) and [Greedy: sum of positive differences](#greedy-sum-of-positive-differences-unlimited-transactions).

### 21. Majority Element II
- **`majorityElement` (hash map):** count each value and push it the moment its count goes above `n/3`. Setting the count to `INT_MIN` afterwards stops it being pushed again. A simpler check is `if (++mp[n] == n/3 + 1)`: it's true exactly once per value, with no sentinel.
- **`majorityElementBoyerMoore`:** two candidates and two counts, then a second pass to count each candidate for real. O(n) time, O(1) space.
- **Bug found by the tests:** both candidates start at the same value (first `-1`, then `INT_MIN`). If the input contains that value and `cd2` is never replaced, `cd1 == cd2`, both counts include it, and it's returned twice (`[-1]` → `[-1, -1]`, `[INT_MIN]` → `[INT_MIN, INT_MIN]`). Changing the starting value only moves the bug, because any `int` can appear in the input. **Fixed** by making the second `if` in the verification loop an `else if`, so one value can't be counted for both candidates (checking `cd1 != cd2` before pushing `cd2` also works).
- "More than `n/3`" is strict: in `[1, 1, 2, 2, 3, 3]` nothing qualifies, and in `[1, 2, 2, 2, 1, 1, 1, 1, 1, 1]` the `2` appears exactly `10/3 = 3` times, so only `1` is returned.
- Answers can come back in any order, so the tests compare sorted results.
- Edge cases tested: empty, single, two different values, all the same, nothing above `n/3`, exactly `n/3`, negatives, `-1` and `INT_MIN` (starting values that were tried), `INT_MIN`/`INT_MAX`. A random cross-check runs 1000 arrays (length 0–30, values −2…3) and compares Boyer-Moore with the hash map version.
- See [Boyer-Moore Voting Algorithm](#boyer-moore-voting-algorithm).

### 22. Subarray Sum Equals K
- One pass: running `currSum`, add `mp[currSum - k]` to the total, then `mp[currSum]++`. `mp[0] = 1` stands for the empty prefix, so a subarray starting at index 0 is counted.
- The lookup order matters: look up **before** inserting `currSum`, otherwise `k == 0` counts each empty subarray.
- `mp[currSum - k]` inserts a `0` entry for every miss. That's harmless for the answer but grows the map; `find` avoids it.
- `int` is enough under LeetCode's limits (`n ≤ 2·10⁴`, `|nums[i]| ≤ 1000` → `|sum| ≤ 2·10⁷`). Use `long long` if the limits are bigger.
- Edge cases tested: empty, single element, no match, whole array, negatives, `k = 0` with zeros (`[0, 0, 0]` → 6), negative `k`, repeated prefix sums. A random cross-check runs 1000 arrays (length 0–50, values −3…3, `k` in −5…5) against an O(n²) brute force.
- See [Prefix sum + hash map](#prefix-sum--hash-map-count-subarrays-with-sum-k).

### 23. First Missing Positive
- **Key fact:** the answer is always in `1..n+1`. With `n` slots, the best case is that `1..n` are all present, and then the answer is `n + 1`. Anything `<= 0` or `> n` can be ignored.
- **`firstMissingPositive` (bool array):** mark `present[v]` for every `v` in `1..n`, then return the first unmarked index. Size `n + 1` is enough (not `1e6`) because of the key fact above. O(n) time and space.
- **`firstMissingPositiveInPlace` (sign marking):** replace `<= 0` with `n + 2` (anything `> n` works, `n + 1` too), mark `v` by making `nums[v - 1]` negative, then the first positive index `i` means `i + 1` is missing. O(n) time, O(1) extra space.
- **`firstMissingPositiveCyclic` (cyclic sort):** swap each `v` in `1..n` to index `v - 1` while the target slot doesn't already hold it, then return the first `i + 1` with `nums[i] != i + 1`. O(n) time (at most `n` swaps in total), O(1) extra space. The first draft had a redundant `j` copy of the loop index and a redundant `nums[j] != j + 1` check, both removed.
- Both versions originally had the same name, so the file didn't compile; the second was renamed to `firstMissingPositiveInPlace`.
- In the in-place version, `val != 0` is always true after the first loop, since every `<= 0` value was replaced.
- `abs(INT_MIN)` would overflow, but it can't happen here: negatives are replaced before anything calls `abs`, and the marks we write are at least `-n`.
- The in-place version changes the caller's array. Note that in an interview, or copy the input first if the caller still needs it.
- Edge cases tested: empty, single `1` / `2`, all non-positive, a permutation of `1..n`, duplicates, values `n`, `n + 1` and `n + 2` (the replacement value), `INT_MIN`/`INT_MAX`. Every case runs against all three versions. A random cross-check runs 1000 arrays (length 0–30, values −5…35) and compares the in-place and cyclic versions with the bool array version.
- See [Using the array as its own hash set](#using-the-array-as-its-own-hash-set-sign-marking) and [Cyclic sort](#cyclic-sort-place-each-value-at-index-v---1).
