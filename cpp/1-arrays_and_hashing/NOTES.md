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

## Boyer-Moore Voting Algorithm
- Keep a `candidate` and a `count`. Same element as candidate → `count++`; different → `count--`. When `count` hits 0, the current element becomes the new candidate.
- Intuition: every non-majority element can "cancel" at most one majority vote. Since the majority appears more than `n/2` times, it's the only one that can survive.
- O(n) time, **O(1) space** (vs O(n) space for the hash map counting approach).
- **Catch:** it assumes a majority exists. If that's not guaranteed, do a second pass to verify the candidate's count is `> n/2`.

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

`k` = alphabet size or string length (#13: number of distinct values), `m` = length of shortest string, `u` = number of unique values.

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
