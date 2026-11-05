# Sliding Window — Notes

The concepts come first, for a quick revision. The problem-by-problem notes are at the end, for when you want more detail.

# Concepts

## Sliding window in general
- A window is a contiguous range `[l, r]` that only moves **forward**. Each step adds `nums[r]` and sometimes removes `nums[l]`. Each element enters once and leaves at most once, so the scan is **O(n)** plus whatever each add or remove costs.
- It's the same-direction two-pointer idea (see the [Two Pointers notes](../2-two-pointers/NOTES.md)) with **state** kept for the elements inside the window: a set, a count map, a running sum.
- **Fixed size `k`:** add `nums[i]`, and once `i >= k` remove `nums[i - k]`, which just left. No `l` is needed. Build the first window separately and start `best` from it, not from a sentinel like `INT_MIN` (the same lesson as Kadane):
  ```cpp
  long long sum = 0;
  for (int i = 0; i < k; i++) sum += nums[i];
  long long best = sum;
  for (int i = k; i < n; i++) {
      sum += nums[i] - nums[i - k];
      best = max(best, sum);
  }
  ```
- **Variable size:** grow `r` every step, and shrink `l` while the window breaks the rule. Before writing the loop, say which rule you're checking.
- **Record the answer only when the window is valid:**
  - **Longest** valid window: add `s[r]`, shrink `l` **while** invalid, **then** record `r - l + 1`. Recording straight after growing can count an invalid window.
  - **Shortest** valid window (Minimum Window Substring): record **inside** the shrink loop, before each shrink, while the window is still valid.
  - An alternative for "longest" is to grow only when the new element keeps the window valid (otherwise shrink). Then recording after growing is right. It's still O(n).

## When a window doesn't work
- Shrinking when the sum is "too big" assumes the sum only goes up as the window grows, which means **non-negative values**. With negatives, a start you discard could have reached the target later.
- "Subarrays with sum exactly `k`" with negatives → **prefix sum + hash map of prefix counts** (see [Prefix sum + hash map](../1-arrays_and_hashing/NOTES.md#prefix-sum--hash-map-count-subarrays-with-sum-k)).
- Check what `k` means: a **length** ("every window of size `k`", "at most `k` apart") suggests a fixed window; a **target sum** doesn't.

## Fixed window with a set ("within distance k")
- "Two equal values at most `k` apart" means "is `nums[i]` already among the previous `k` elements?" So keep **only those `k` elements** in a set.
- At index `i`, the window holds indices `[i - k, i - 1]`. When `i > k`, erase `nums[i - k - 1]`, check whether `nums[i]` is in the set, then insert it.
- Space is **O(min(n, k))** instead of O(n), because the set never holds more than `k` values.
- When a problem says "within distance k", "at most k apart" or "in every window of size k", think **fixed window plus a set or count map**.
- The alternative is a map from value to **last index seen**. The closest earlier copy is the only one that can be within `k`, so the latest index is enough. That's O(n) space, but it's simple and also correct.

## Jump `l` past the last copy (variable window)
- Instead of shrinking `l` one step at a time until the repeat is gone, store each value's **last index** and move `l` there in one step: `l = max(l, last[x] + 1)`.
- The `max` matters: `last[x]` can point to a copy that's already **outside** the window. Without the `max`, `l` would jump backwards. Example: `"abba"` at `r = 3`, where `last['a'] + 1 = 1` but `l` is already 2.
- With `last` filled with `-1`, `max(l, -1 + 1)` is just `l`, so no `if (last[x] != -1)` check is needed.
- It's still O(n), like shrinking one step at a time, but it's one pass instead of up to two and needs no erase. It's a common interview follow-up: "can you avoid moving `l` one step at a time?"
- Size the table by the alphabet: 128 for ASCII, 26 for lowercase (`c - 'a'`), a map for Unicode. Index with `(unsigned char) c` if bytes above 127 are possible.

## Window validity as a count (Character Replacement)
- "Can this window become all one letter with at most `k` replacements?" Keep the **most frequent** letter and replace everything else, so the cost is `len - maxFreq`. The window is valid when `len - maxFreq <= k`.
- Look for the single number that decides validity before writing a check that tries every option. Trying every letter as the one to keep (26 × 26 per check) gives the same answer, because the minimum over all letters is the most frequent one.
- `maxFreq` over a 26-entry count array is an O(26) scan, so the whole solution is O(26·n). That's fine at L4.
- **Follow-up (O(n)):** keep `maxFreq` as a running max that **never decreases** when `l` moves. A stale, too-high `maxFreq` can only keep the window at its current size; it never records a longer invalid window. The answer only grows when a real higher frequency appears. Know the argument; you don't need to lead with it.
- Since the window never needs to shrink below the best length seen, `if` can replace `while` for the shrink (move `l` once per step). The window then slides at the best size instead of shrinking.

## Fixed window with count arrays (anagrams and permutations)
- "Does the text contain a permutation (anagram) of the pattern?" The window is fixed at the pattern's length. Keep a count array for the pattern and one for the window; slide by adding `text[i]` and removing `text[i - k]`.
- Comparing the two arrays is O(26) per step, so O(26·n) overall. That's fine at L4.
- `vector<int>` (and `array<int, 26>`) has `==` that compares element by element, so `if (winCount == patCount)` replaces a hand-written helper loop.
- **Follow-up (O(n)):** keep `matches`, the number of letters whose counts agree. When a count changes, check whether that letter stopped or started matching, and return when `matches == 26`.
- Same pattern: Find All Anagrams in a String (LC 438), which collects every start index instead of returning early.

## One hash lookup instead of two
- `s.insert(x)` returns a `pair<iterator, bool>`, where `.second` is `false` if `x` was already in the set. `if (!s.insert(x).second) return true;` checks and inserts with one hash operation instead of two (`contains`, then `insert`).
- On a map, `mp.contains(n)` followed by `mp[n]` also looks the key up twice. `find` returns an iterator to a `pair<const Key, Value>`, so the value is `it->second`:
  ```cpp
  auto it = mp.find(n);
  if (it != mp.end() && i - it->second <= k) return true;
  ```
  (Also see [`operator[]` on a map inserts missing keys](../2-two-pointers/NOTES.md#operator-on-a-map-inserts-missing-keys).)
- **Check and update in one lookup:** `try_emplace(key, value)` inserts only when the key is missing, and returns `(iterator, inserted)` like `insert`:
  ```cpp
  auto [it, inserted] = mp.try_emplace(n, i);
  if (!inserted) {
      if (i - it->second <= k) return true;
      it->second = i;
  }
  ```
- This won't change the big-O, but an HFT interviewer will notice the extra hashing.

# Problems

| # | Problem | File | Approach | Time | Space |
|---|---------|------|----------|------|-------|
| 1 | Contains Duplicate II | [contains_duplicate.cpp](contains_duplicate.cpp) | Fixed window of the last `k` values in a set; erase `nums[i - k - 1]` when `i > k`. (Also a last-index map, and an O(n·k) scan over gaps) | O(n) | O(min(n, k)) |
| 2 | Maximum Average Subarray I | [Q02 coding question](../quizzes/flashcards/q02_2026-11-05.md) | Fixed window of size `k` with a running sum; cast to `double` before dividing | O(n) | O(1) |
| 3 | Best Time to Buy and Sell Stock | [best_time_to_buy_sell_stock.cpp](best_time_to_buy_sell_stock.cpp) | Keep the minimum price so far; the best profit is `max(p - minSoFar)` | O(n) | O(1) |
| 4 | Longest Substring Without Repeating Characters | [longest_substr_without_rep_chars.cpp](longest_substr_without_rep_chars.cpp) | Set window: grow while the char is new, else erase from `l` until it is. Optimal: last index per char, `l = max(l, last[c] + 1)` | O(n) | O(min(n, 128)) |
| 5 | Longest Repeating Character Replacement | [longest_repeating_char_replacement.cpp](longest_repeating_char_replacement.cpp) | Count array; the window is valid when `len - maxFreq <= k`; shrink `l` while invalid. Optimal: running `maxFreq` that never decreases. (Also one window per target letter) | O(n) | O(26) |
| 6 | Permutation in String | [permutation_of_string.cpp](permutation_of_string.cpp) | Fixed window of the pattern's length with 26-entry count arrays; compare with `==`. Optimal: a `matches` counter of letters that agree, updated per change | O(n) | O(26) |

Harnesses are skipped while preparing for the interview. Solutions are checked on LeetCode instead.

### 1. Contains Duplicate II
- **Time taken:** the hash-map and naive versions took 15 minutes. The set version was learned after reading the approach. At L4, aim for about 10 minutes on an easy, and reach the best approach without help.
- **`containsDuplicateNaive`:** for each gap `i` from 1 to `k`, compare `nums[j]` with `nums[j - i]`. O(n·k) time, O(1) space. When `k >= n`, the extra gaps just do nothing.
- **`containsDuplicateHashMap`:** maps each value to the index where it was last seen, and returns `true` when `i - mp[n] <= k`. O(n) time, O(n) space. `mp.contains(n)` followed by `mp[n]` looks the key up twice; a single `find` does it once (see [One hash lookup instead of two](#one-hash-lookup-instead-of-two)).
- **`containsDuplicateSpaceOptimized`:** the set holds the last `k` values. O(n) time, O(min(n, k)) space. See [Fixed window with a set](#fixed-window-with-a-set-within-distance-k).
  - `if (!s.insert(nums[i]).second) return true;` would replace the separate `contains` and `insert`.
- Add a one-line complexity comment above each version. In an interview, state the complexity before the interviewer asks.

### 2. Maximum Average Subarray I
- Written in quiz Q02 without compiling, and correct the first time, including `k == n`.
- **Sum type:** `int` would also fit (`10⁵ · 10⁴ = 10⁹ < 2.147·10⁹`), but `long long` is the right habit. Check the bound either way.
- **Average:** `(double) best / k`. Cast before dividing, or `long long / int` does integer division.
- It started `maxSum` at `INT_MIN` and used an `if`/`else` inside one loop. Building the first window separately removes both (see the fixed-size template under [Sliding window in general](#sliding-window-in-general)).

### 3. Best Time to Buy and Sell Stock
- **Time taken:** 8 minutes, solved alone.
- **`maxProfit`:** for each price, update `best = max(best, p - minSoFar)`, then `minSoFar = min(minSoFar, p)`. Updating the profit first means you never sell on the day you buy. Starting `best` at 0 covers "no profitable trade".
- As a window: `l` sits at the cheapest day so far and `r` is today. When a cheaper day appears, `l` jumps to it.
- It starts `minUntilNow` at `INT_MAX / 2`. Start from `prices[0]` instead (the same lesson as Kadane): no sentinel to reason about.
- With unlimited trades, the answer is the sum of every positive daily difference instead (see [Arrays & Hashing](../1-arrays_and_hashing/NOTES.md#greedy-sum-of-positive-differences-unlimited-transactions)).

### 4. Longest Substring Without Repeating Characters
- **Time taken:** 20 minutes for the set version, solved alone. That is inside the 25-minute target for a medium.
- **`lenLongestSubstr` (set):** grows `r` while `s.insert(str[r]).second` succeeds, recording the length each time. When a repeat appears, it erases `str[l++]` until the repeat is gone. Correct, O(n). It uses `insert().second` from [One hash lookup instead of two](#one-hash-lookup-instead-of-two).
  - Three nested `while` loops are harder to trace and to argue O(n) for than the standard `for` template. In `while (l < r && r < n && ...)`, `l < r` and `r < n` are always true when it runs, so neither guard is needed. The standard template:
    ```cpp
    for (int r = 0; r < n; r++) {
        while (s.contains(str[r])) s.erase(str[l++]);
        s.insert(str[r]);
        maxLen = max(maxLen, r - l + 1);
    }
    ```
- **`lenLongestSubstrOpt` (jump):** last index per char in a `vector<int>(128, -1)`, `l = max(l, charMap[s[r]] + 1)`. Correct. The `if (charMap[s[r]] != -1)` isn't needed (see [Jump `l` past the last copy](#jump-l-past-the-last-copy-variable-window)). Learned from the solution.
- Both take `string` **by value**, which copies the input. They only read it, so use `const string&` (see [Copy or reference for a string parameter](../2-two-pointers/NOTES.md#copy-or-reference-for-a-string-parameter)). This is the third time this slip has come up.
- **Traces:** the trace comments list only the **final** values, so they can't show where a step went wrong. The `"abba"` trace has `a: 0`, but after `r = 3` it's `a: 3`, and the return value is left blank (it's 2). Write each variable's history instead (`l: 0 0 2 2`), as in the interview trace method.

### 5. Longest Repeating Character Replacement
- **Time taken:** 50 minutes, with some wrong attempts, solved alone. That's double the target. Next time, stop at 15 minutes with no clear validity rule and read the approach.
- **`characterReplacement`:** a count array of 26; add `s[r]`; if the window is valid, record its length, otherwise shrink `l` until it's valid. The windowing is correct. Nothing needs recording after shrinking, because the window just before adding `r` was valid and at least as long.
- **`substrIsValid`:** tries every letter as the one to keep and adds up the other counts, so 26 × 26 per call. That's the same as `len - maxFreq <= k` (see [Window validity as a count](#window-validity-as-a-count-character-replacement)), which is one 26-scan or O(1) with a running `maxFreq`.
- The saved file is now correct (`charCount[i]`). Random cross-check of all three versions: 20,000 strings over `"ABC"` (length 0–11, `k` 0–3), no mismatches.
- **Doesn't compile as a standalone file:** `substrIsValid` is defined after `characterReplacement` uses it. On LeetCode both are members of `Solution`, where order doesn't matter. In a file, declare it first or move it above.
- The `continue` after recording is redundant next to the `else`.
- **Trace:** the `"AAB"` trace is right. In `"ABCC"`, the final count is `{C: 2}`, not `{C: 1}`.
- **`charReplacementMaxLen` + `charReplacement26` (one window per target letter):** for each distinct letter `c`, run a window where the cost is "chars that aren't `c`", and keep the best. O(m·n) for `m` distinct letters (at most 26). Correct, and a good stepping stone: with a fixed target letter, validity is a single counter.
- **`charReplON` (optimal, learned after the break):** `maxf` is a running max that never decreases, `while (len - maxf > k)` shrinks, then records. Correct, O(n).
  - **Why `maxf` never has to decrease:** the answer only grows when a window has `len - maxf <= k` with a **larger** `len`, and that needs a real frequency above the old `maxf`. A stale, too-high `maxf` only lets the window slide at its current size; it never records a longer one. Be ready to say this in two sentences. It's the part interviewers ask about.
  - Use `vector<int>(26)` instead of `unordered_map<char, int>`: the input is uppercase letters only. `maxf = max(maxf, ++count[s[r] - 'A'])` does the increment and the read in one step.
- **`string&` parameters:** both new functions take a non-const `string&`. They only read `s`, so use `const string&`. This is the 4th time the parameter-type slip has come up.

### 6. Permutation in String
- **Time taken:** under 20 minutes, found alone. Inside the target for a medium.
- **`checkInclusion`:** count arrays for the pattern and the first window, compare with `==`, then slide one step at a time. Correct, O(26·n) time, O(26) space.
- **`checkInclusionOpti` (`matches` counter):** counts how many of the 26 letters agree. When one count changes, it goes up if the letter now matches, and down if it matched just before the change. It checks at the top of each step and once more after the loop for the last window. Correct, O(n + 26) time, O(26) space.
- Both versions agree with a brute force on 50,000 random cases.
- **Argument order:** both functions treat `s1` as the text and `s2` as the pattern. LC 567 says the opposite ("return true if `s2` contains a permutation of `s1`"), so `checkInclusion("ab", "eidbaooo")` returns `false` where LeetCode expects `true`. That's fine as a deliberate variant, but before coding in an interview, restate which argument is which.
- `const string&` and `const vector<int>&` are used throughout. That's the parameter habit fixed.
- **Traces:** the first columns are snapshots and the last column is updated in place, which is quicker to write. Both are right: `"clear"` / `"aer"` returns at `i = 4` on the window `"ear"`, and `"abec"` / `"ce"` ends with `matches: 26`. Worth knowing for the explanation: right after the first-window count, `matches` is **22**, not 0, because the 22 letters missing from both strings already match at `0 == 0`. That's why the target is 26 and not the number of distinct letters.
