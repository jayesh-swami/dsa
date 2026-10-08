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

`k` = alphabet size or string length, `m` = length of shortest string.

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
