# Quiz 1: Arrays & Hashing (graded)

## Result: 82 / 103 (80%)

| Section | Score |
|---|---|
| 1. Complexity and constraints | 5.5 / 7 |
| 2. Hashing | 9 / 11 |
| 3. Prefix sums | 15 / 17 |
| 4. Kadane and greedy | 6 / 10 |
| 5. Boyer-Moore voting | 5.5 / 6 |
| 6. In-place array tricks | 8.5 / 10 |
| 7. Sorting and selection | 11.5 / 12 |
| 8. Monotonic stack and encoding | 4.5 / 5 |
| 9. C++ | **4 / 10** |
| 10. Contest-style problems | 12.5 / 15 |

**Strong:** prefix sums (you worked out the difference array and the 0/1 → ±1 trick on your own), hashing internals, in-place tricks, sorting. The code you wrote for 3.6, 3.8 and 6.6 all passed a randomised check against brute force.

**What to work on**
1. **C++ for contests (section 9).** Integer types and overflow (`int * int`, unsigned `size()`), `priority_queue`, and fast I/O. These bugs cost you a verdict even when the algorithm is right, so they're the cheapest marks to win back.
2. **`long long` for pair counts.** Counting pairs can give up to `n(n-1)/2 ≈ 2·10¹⁰` for `n = 2·10⁵`, which overflows `int`. You missed this in P1, P2 and P5.
3. **Small slips when tracing by hand:** 1.1 (O(n²) at `n = 2·10⁵`), 4.4 (stock profits), 8.1 (nearest, not first), 3.1 (missed a subarray). Write the trace out step by step instead of doing it in your head.
4. **Answer every part.** 3.2, 4.2 and 3.6 each lost marks for a part that was asked but not answered.

**Key:** ✅ full marks · 🟡 partial · ❌ no marks

---

## 1. Complexity and constraints

**1.1** [1] A judge runs about 10⁸ simple operations per second. Here `n ≤ 2·10⁵` and the time limit is 1 s. Which complexities fit comfortably? *(select all)*

- A. O(n²)
- B. O(n log n)
- C. O(n)
- D. O(n log² n)

**Answer:** A,B,C

> ❌ **0 / 1.** Correct: **B, C, D.**
> - O(n²) = (2·10⁵)² = 4·10¹⁰ operations, which is about 400 s. That's far too slow.
> - O(n log² n) ≈ 2·10⁵ × 18² ≈ 6.5·10⁷, which fits.
> - Rough rule of thumb: `n ≤ 10⁵–10⁶` → O(n) or O(n log n); `n ≤ 5000` → O(n²); `n ≤ 500` → O(n³); `n ≤ 20` → O(2ⁿ).

**1.2** [2] You don't know the intended solution yet, but you can read the constraints. What complexity is the setter probably hinting at for **(a)** `n ≤ 5000`, and **(b)** `n ≤ 20`?

**Answer:** O(n^2) for a and O(2^n) for b

> ✅ **2 / 2.** For (b), O(2ⁿ · n) also fits, e.g. trying every subset and spending O(n) on each.

**1.3** [2] The monotonic stack sweep has a `while` (popping) inside a `for`, but it's O(n), not O(n²). Explain why in one or two sentences.

**Answer:** Because each element will only be inserted and popped at max once from the stack.

> ✅ **2 / 2.** That's the amortised argument: there are at most `n` pops across the whole sweep, so all the `while` loops together do O(n) work.

**1.4** [2] In Longest Consecutive Sequence, a friend only counts up from `x` when `x - 1` is absent, which is correct. But they loop over the **input array** instead of the set. Describe an input where their solution becomes O(n²).

**Answer:** {1, 1, 1, 1, 1, 2, 3} Where there are multiple starts

> 🟡 **1.5 / 2.** The idea is right: duplicates of a run start each walk the whole run again. To get O(n²), though, you need **both** many copies **and** a long run. For example, use `n/2` copies of `1` followed by `2, 3, …, n/2`. Each of the `n/2` copies walks `n/2` steps, which gives `n²/4`. Your example walks 3 steps 5 times.

---

## 2. Hashing

**2.1** [1] `m` is an `unordered_map<int, int>` and `x` is **not** in it. Which of these leave `m` unchanged? *(select all)*

- A. `m[x]`
- B. `m.find(x)`
- C. `m.count(x)`
- D. `m.contains(x)`
- E. `if (m[x] == 0) { ... }`

**Answer:** B, C, D

> ✅ **1 / 1.**

**2.2** [1] This Two Sum **inserts before it looks up**:

```cpp
unordered_map<int, int> seen;
for (int i = 0; i < nums.size(); i++) {
    seen[nums[i]] = i;
    if (seen.count(target - nums[i]))
        return {seen[target - nums[i]], i};
}
return {};
```

What does it return for `nums = [3, 2, 4]`, `target = 6`?

- A. `{1, 2}`
- B. `{0, 0}`
- C. `{}`
- D. `{0, 2}`

**Answer:** B

> ✅ **1 / 1.** `3` finds itself as its own complement.

**2.3** [2] For Group Anagrams, someone avoids sorting by building the key from character counts. They loop over the 26 letters and append `to_string(count[c])` to the key. Give two strings that are **not** anagrams but get the same key, and say how to fix the key.

**Answer:** "aas" "bbs" would give the same key here. To fix it also add the character as part of the key.

> 🟡 **1 / 2.** The fix is right, but the example doesn't collide. The counts are written **in letter order**, so `"aas"` gives `"2000…010…"` and `"bbs"` gives `"0200…010…"`, which are different keys.
> - The real problem is that numbers with more than one digit have no boundaries. Take `"a" + 11×"b"` (counts `a=1, b=11`) and `11×"a" + "b"` (counts `a=11, b=1`). Both produce `"111000…"`.
> - Adding the letter works because the letters act as separators (`a1b11` vs `a11b1`). A `#` between counts works too, and so does storing each count as a single `char`.

**2.4** [2] (a) What is `-10 % 7` in C++? (b) Write an expression that always gives `x mod m` in `[0, m)`, even when `x` is negative.

**Answer:** -3. `(x % m) < 0 ? m + (x % m) : (x % m)`

> ✅ **2 / 2.** A shorter version without a branch, common in contest code: `((x % m) + m) % m`.

**2.5** [2] A linear-probing hash set uses `h(k) = k % 7`. Its `remove` sets the slot back to `EMPTY` (no tombstones). You run `add(3)`, `add(10)`, `remove(3)`, then `contains(10)`. What does `contains(10)` return, and why? What would a tombstone change?

**Answer:** Here contains would return `false` in traditional implementation because it would check in 3rd slot and find that it is empty and stop and return `false`. Tombstone would allow it to continue its search in case it was inserted in one of the next empty slots.

> ✅ **2 / 2.** `10` was probed past slot 3 into slot 4. A `DELETED` slot tells the lookup "something used to be here, keep going".

**2.6** [1] Why is a prime table size usually preferred?

- A. Computing `% p` is faster for a prime `p`
- B. Keys that share a common factor with the table size would otherwise crowd into a few buckets
- C. Linear probing doesn't terminate otherwise
- D. It uses less memory

**Answer:** B

> ✅ **1 / 1.**

**2.7** ★ [2] On Codeforces, a solution using `unordered_map<long long, int>` passes all the pretests, but someone hacks it with a TLE. Based on what you know about how hash tables work inside, how could a specially built input cause this? Name one way to defend against it.

**Answer:** Don't know what is meant by hacking with time limit exceeded. but if you mean that they caused TLE by changing the inbuilt hashing function and caused it to create long chains instead of spreading the keys thereby reducing performance, then one way could be to not allow changing of the inbuilt hash function of unordered although I have no clue how to do that or maybe change the default hash implementation. But again this is me going off from my assumption of what hack with TLE means.

> 🟡 **1 / 2.** You got the consequence (long chains) and the defence (replace the default hash). The mechanism is different, though.
> - **What a hack is:** in a Codeforces round, other contestants can read your accepted code and submit an **input** that breaks it. If it breaks, your solution fails.
> - **How it works:** nobody touches your hash function. For integers, `std::hash` is just the identity, and the bucket count follows a fixed, public sequence of primes. So the attacker picks **keys** that are all multiples of that prime. Every key lands in the same bucket, each operation becomes O(n), and the whole run becomes O(n²). It's the same "common factor" problem as 2.6, done on purpose.
> - **Defence:** a custom hash with a **random seed** chosen at runtime, so the attacker can't predict the buckets. The standard choice is splitmix64 seeded from `chrono::steady_clock`, passed as `unordered_map<long long, int, custom_hash>`. You can also avoid hashing entirely: use `map` (O(log n), can't be attacked), or sort and coordinate-compress.

---

## 3. Prefix sums

**3.1** [1] Subarray Sum Equals K with `nums = [1, -1, 0]` and `k = 0`. How many subarrays sum to `k`?

- A. 1
- B. 2
- C. 3
- D. 4

**Answer:** C (assuming empty array is valid subarray, if not then B)

> 🟡 **0.5 / 1.** **C** is right **without** counting empty subarrays. The three are `[1, -1]`, `[0]` and `[1, -1, 0]`, and it looks like you missed the whole array. (If empty subarrays counted, there would be 4 more, one at each gap, so 7 in total.) Prefixes are `0, 1, 0, 0`, and three pairs are equal.

**3.2** [2] Someone forgets to seed the map with `count[0] = 1`. For `nums = [3, 4, 7]` and `k = 7`, what does their code return, and what is the correct answer? Which subarrays does the bug always miss?

**Answer:** It will miss the first subarray from left that matches the sum so in this case `[3, 4]`.

> 🟡 **1 / 2.** It returns **1** (only `[7]`), and the correct answer is **2**. The two numbers weren't stated.
> - The general rule is a bit off. The bug misses **every subarray that starts at index 0**, not just the first match. With `[7, 0]` and `k = 7`, it misses both `[7]` and `[7, 0]`.
> - Those subarrays need "prefix before index 0", which is the empty prefix with sum 0, and that's exactly what the seed provides.

**3.3** [2] Give a concrete counterexample where a sliding window (grow right while the sum is `< k`, shrink left while it's `> k`) fails to find a subarray with sum `k`, and say why it fails.

**Answer:** The approach fails with negative numbers in an array. For eg. `[3,2,-1,7]` with `k = 4`. The algorithm would get to the window `{3,2}`, see that it is more than k and shrink it to just `{2}`, and we will miss the answer subarray which is `[3, 2, -1]`.

> ✅ **2 / 2.** Good counterexample (I checked it). The underlying reason: with negatives, growing the window can **decrease** the sum. So "too big → shrink" isn't safe, because a later negative could have fixed it.

**3.4** [2] Now find the **longest** subarray with sum `k`. What does the map store, what do you seed it with, and why do you never overwrite an entry once it's set?

**Answer:** The map stores the first index a particular sum was seen from the left. We seed it with `mp[0] = -1` if we calculate the length as `currIndex - mp[currSum - k]`. We never overwrite because the first seen entry is bound to give us the longest possible array.

> ✅ **2 / 2.**

**3.5** [2] Count the subarrays whose sum is **divisible by `m`**. What do you use as the map key, and what C++ pitfall do you have to handle when the array has negatives?

**Answer:** We would use the map key as the `(prefix sum) % m` (adjusted for negative values) and the value as count. We would need to make sure that modulo always returns a positive value.

> ✅ **2 / 2.** Also seed with `count[0] = 1`, as in 3.2. And since the keys are in `[0, m)`, a `vector<int>(m)` can replace the map.

**3.6** ★ [3] Given a binary array (`n ≤ 10⁵`), find the length of the longest subarray with an equal number of 0s and 1s. Give the approach and its complexity.

**Answer:** The approach is longest subarray with sum k. Where 0 decrement and 1 increment the current sum and `k = 0`.

```c
int longestEqualBinarySubarray(vector<int>& nums) {
	int currSum = 0;
	int longestSubArrayLen = 0;
	unordered_map<int, int> mp;
	mp[0] = -1;

	for(int i = 0; i < (int) nums.size(); i++) {
		if(nums[i]) currSum++;
		else currSum--;
		if(!mp.contains(currSum)) mp[currSum] = i;

		longestSubArrayLen = max(longestSubArrayLen, i - mp[currSum]);
	}

	return longestSubArrayLen;
}
```

> 🟡 **2.5 / 3.** Correct reduction and correct code (it matched brute force on 2000 random arrays). Inserting before the lookup is fine here, because a new sum just gives length 0. You left out the complexity, which the question asked for: **O(n) time, O(n) space**.
> - Contest tip: the running sum is always in `[-n, n]`, so a `vector<int>(2n + 1, -2)` indexed by `sum + n` is faster than a hash map.

**3.7** [2] `P` is a zero-padded 2D prefix sum of size `(n+1) × (m+1)`, so `P[i+1][j+1]` is the sum of the rectangle from `(0, 0)` to `(i, j)`. Write the sum of the rectangle from `(r1, c1)` to `(r2, c2)` (inclusive, 0-indexed) in terms of `P`.

**Answer:** `P[r2+1][c2+1] - P[r1][c2+1] - P[r2+1][c1] + P[r1][c1];` 

> ✅ **2 / 2.**

**3.8** ★ [3] You get an array of `n` zeros and `q` updates of the form "add `v` to every element in `a[l..r]`". After all updates, print the array. `n, q ≤ 2·10⁵`. Doing each update in a loop is O(n·q), which is too slow. Give an O(n + q) approach. *(Hint: think of prefix sums run backwards.)*

**Answer:** 
```c
/**
 * You get an array of `n` zeros and `q` updates of the form "add `v` to 
 * every element in `a[l..r]`". After all updates, print the array. 
 * `n, q ≤ 2·10⁵`. Doing each update in a loop is O(n·q), 
 * which is too slow. Give an O(n + q) approach.
 *
 * queries are of form {v , {l, r}}
 * assuming [l, r] are both inclusive
 */
vector<int> getArrayAfterQueries(int n, vector<pair<int, pair<int, int>>>& queries) {
	vector<int> res(n, 0), add_k(n, 0);

	for(auto& p: queries) {
		add_k[p.second.first] += p.first;
		if(p.second.second + 1 < n)
			add_k[p.second.second + 1] -= p.first;
	}

	int currVal = 0;

	for(int i = 0; i < n; i++) {
		currVal += add_k[i];
		res[i] = currVal;
	}

	return res;
}
```

> ✅ **3 / 3.** This is the **difference array** technique, and you derived it yourself (it matched brute force on random tests).
> - One contest note: with `v` up to 10⁹ and `q = 2·10⁵`, values reach 2·10¹⁴, so use `long long`.
> - Sizing `add_k` as `n + 1` removes the `if` as well.

---

## 4. Kadane and greedy

**4.1** [1] What is the maximum subarray sum of `[5, -9, 6, -2, 3]` (non-empty)?

- A. 6
- B. 7
- C. 9
- D. 5

**Answer:** B

> ✅ **1 / 1.** The subarray is `[6, -2, 3]`.

**4.2** [2] Empty subarrays are **not** allowed. What does this code return for `[-3, -1, -2]`, and what's the one-line fix?

```cpp
int cur = 0, best = 0;
for (int x : nums) {
    cur = max(x, cur + x);
    best = max(best, cur);
}
return best;
```

**Answer:** 0

> 🟡 **1 / 2.** `0` is right. The fix was missing.
> - The fix is `int cur = 0, best = INT_MIN;`, which returns `-1`.
> - `cur = 0` is actually harmless, since the first step is `max(x, 0 + x) = x`. The bug is that `best` starts at `0`, a value no non-empty subarray reached.

**4.3** [2] Why does starting `cur` at `INT_MIN` cause trouble, and what's the cleanest way to initialise instead?

**Answer:** `cur` at `INT_MIN` causes trouble because it can overflow with negative elements when we add them to it. We can do `INT_MIN / 2` if our range allows or if empty subarrays are allowed `cur = 0`
 
> 🟡 **1 / 2.** The overflow reason is right (`INT_MIN + (negative)` is signed overflow, which is UB).
> - `INT_MIN / 2` is a workaround that depends on the value range. The cleanest fix needs no sentinel at all: `cur = best = nums[0]`, then loop from index 1.
> - Alternatively, as in 4.2, `cur = 0` with `best = INT_MIN` is safe.

**4.4** [2] `prices = [1, 5, 3, 8]`. (a) What's the best profit with **unlimited** transactions? (b) With **at most one** transaction? (c) In one sentence, why is the greedy for (a) correct?

**Answer:** a. 7 b. 5 c. Greedy is correct because segmentation into subproblems yield the same result as bigger subproblem. (help with wording when marking pls)

> 🟡 **0.5 / 2.** (a) and (b) are both wrong:
> - **(a) 9.** Buy 1 → sell 5 (+4), buy 3 → sell 8 (+5). Or sum the positive daily differences: `4 + 5`.
> - **(b) 7.** Buy at 1, sell at 8. (7 is the one-trade answer, so it looks like (a) and (b) got mixed up.)
> - **(c)** The idea is there. One way to word it: *"Any trade from day `a` to day `b` earns `prices[b] - prices[a]`, which equals the sum of the daily changes between them. So collecting every positive daily change earns at least as much as any set of trades, because it takes all the ups and skips all the downs."*

**4.5** ★ [3] Maximum **product** subarray. Why does plain Kadane (`cur = max(x, cur * x)`) fail? What extra state fixes it?

**Answer:** It fails because multiplication with negative number would not be accounted for. We can have 2 negatives giving us a big positive number but `curr * x` would become negative and would not be updated to cur (as there might be another negative ahead to make it positive). This is similar to the problem faced by sliding window solution for max subarray sum. Here the solution would be to keep another state that track the minimum subarray product and make it like `cur = max(x , max(curr * x, currMin * x))`

> 🟡 **2.5 / 3.** Correct reasoning and the right extra state. Two things are missing:
> - `curMin` needs its own update, `curMin = min({x, cur * x, curMin * x})`.
> - Both updates must use the **old** values, so save `cur` in a temp first. Otherwise the second line reads the already-updated `cur`.
> - Zeros are handled automatically by the `x` option, which restarts the product.

---

## 5. Boyer-Moore voting

**5.1** [1] Run single-candidate Boyer-Moore on `[2, 2, 1, 1, 1, 2, 2]`. What's the final candidate?

**Answer:** 2

> ✅ **1 / 1.**

**5.2** [1] At most how many distinct values can appear **more than `n/4`** times?

- A. 2
- B. 3
- C. 4
- D. It depends on `n`

**Answer:** B

> ✅ **1 / 1.**

**5.3** [2] Boyer-Moore on `[1, 2, 3]` returns `3`. What does this show, and what must you do when a majority isn't guaranteed?

**Answer:** This shows that single candidate boyer moore only works when majority is guarenteed and same count elements might fight for candidacy otherwise. We much run through the array and check the frequency of our candidate when majority is not guaranteed.

> ✅ **2 / 2.**

**5.4** [2] In the `n/3` version, both candidates start at `-1` and the verification pass uses two separate `if`s. What does it return for `[-1]`, and why? Give one fix.

**Answer:** `{-1, -1}`. The fix would be to do it in an if-else

> 🟡 **1.5 / 2.** The answer and the fix are right, but the "why" was missing. `cd2` is never replaced, so both candidates equal `-1`. In the verification pass, both `if`s match the same element, both counts become 1 (`> 3/3 = 0`), and `-1` is pushed twice.

---

## 6. In-place array tricks

**6.1** [1] For First Missing Positive on an array of length `n`, the answer is always in:

- A. `1..n`
- B. `0..n`
- C. `1..n+1`
- D. `1..max(nums)+1`

**Answer:** C

> ✅ **1 / 1.**

**6.2** [2] This cyclic sort uses `if` where it should use `while`:

```cpp
for (int i = 0; i < n; i++)
    if (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
        swap(nums[i], nums[nums[i] - 1]);
for (int i = 0; i < n; i++)
    if (nums[i] != i + 1) return i + 1;
return n + 1;
```

What does it return for `[2, 3, 4, 1]`, and what's the correct answer?

**Answer:** This algorithm would give us 1. The correct answer is 5.

> ✅ **2 / 2.** The array ends up as `[3, 2, 1, 4]`, because the value swapped into `i` is never placed.

**6.3** [1] In the correct `while` version, you drop the guard `nums[nums[i] - 1] != nums[i]` (keeping the range check). What happens on `[1, 1]`?

- A. Returns 2
- B. Infinite loop
- C. Out-of-bounds access
- D. Returns 1

**Answer:** B

> ✅ **1 / 1.**

**6.4** [2] In the sign-marking version: (a) why replace every value `<= 0` before marking? Give both reasons. (b) Why read values with `abs()`?

**Answer:** a. The 2 reasons would be to prevent out of bounds access and to not mistakenly assume a negative number as a marked number. b. Reading value with `abs` as there might be a marked number in the array which will be negative.

> 🟡 **1.5 / 2.** "Negatives look like marks" is right, and so is (b). Out-of-bounds isn't the second reason: the `1..n` range check already guards the index.
> - The second reason is about the slot as a **flag holder**: a slot holding `0` **can't be marked**, because `-0 == 0`. So the value whose slot it is would look missing.

**6.5** [2] This Dutch national flag has one bug:

```cpp
int low = 0, mid = 0, high = n - 1;
while (mid <= high) {
    if (a[mid] == 0) swap(a[low++], a[mid++]);
    else if (a[mid] == 1) mid++;
    else { swap(a[mid], a[high--]); mid++; }
}
```

What does it produce for `[1, 2, 0]`? Explain the bug.

**Answer:** This would return `[1, 0, 2]`. The bug is doing `mid++` in the else part, as this skips the swap of 0 with 1.

> ✅ **2 / 2.** A more precise way to put it: the value swapped in from `high` **hasn't been examined yet**, so `mid` must stay to classify it. Here that value is the `0`, and moving past it means it never reaches `low`.

**6.6** [2] Remove Duplicates from a **sorted** array in place: keep the first copy of each value and return the new length. Write it with a read and a write pointer (about 5 lines).

**Answer:**
```c
int removeDuplicates(vector<int>& nums) {
	unordered_set<int> s;
	int w = 0;
	
	for(int r = 0; r < (int) nums.size(); r++) {
		if(s.insert(nums[r]).second) {
			swap(nums[r], nums[w++]);
		}
	}

	return w;
}
```

> 🟡 **1 / 2.** It's correct (it passed random tests) and would work even on unsorted input. But it ignores the **sorted** hint and uses O(n) extra space.
> - In a sorted array, duplicates are next to each other, so you only need to compare with the last value you kept. That needs O(1) space and no hashing:
> ```cpp
> if (nums.empty()) return 0;
> int w = 1;
> for (int r = 1; r < nums.size(); r++)
>     if (nums[r] != nums[w - 1]) nums[w++] = nums[r];
> return w;
> ```
> - Lesson: when a problem says "sorted", ask what that lets you drop.

---

## 7. Sorting and selection

**7.1** [1] Which are stable? *(select all)*

- A. Bubble sort
- B. Selection sort
- C. Insertion sort
- D. Merge sort
- E. Quick sort (Lomuto)
- F. `std::sort`
- G. `std::stable_sort`

**Answer:** A, C, D, G

> ✅ **1 / 1.**

**7.2** [2] Describe a situation where you *need* a stable sort to get the right answer.

**Answer:** An example would be sorting on multiple keys of an object, first on a then on b. In these scenarios we rely on stable sorting to maintain the order of the current elements.

> ✅ **2 / 2.** Note the order: sort by the **secondary** key first, then stable-sort by the **primary** key. Ties on the primary key then keep their secondary order.

**7.3** [1] In merge sort's merge, you take from the left half only when `left < right` (instead of `<=`). The result is:

- A. Still stable
- B. Sorted but no longer stable
- C. Not sorted correctly
- D. O(n²)

**Answer:** B

> ✅ **1 / 1.**

**7.4** [2] Quick sort with a **random** pivot and Lomuto partition (`<` comparison) on an array of 10⁵ equal values. What's the complexity, why, and what fixes it?

**Answer:** O(n ^ 2) because each time the partition length would be `1` and `p-1` starting from n. We can fix this by doing a 3 way partition of less than, equals and more than.

> ✅ **2 / 2.**

**7.5** [2] Every element is at most 3 positions away from its sorted position. Among bubble, selection, insertion and merge sort, which is the best choice, and what's its complexity here?

**Answer:** Insertion sort as it would be max 3 swaps per element. O(3 *n)

> ✅ **2 / 2.** O(n·d) in general, which is O(n) here.

**7.6** [2] You need the 10 **largest values** from `n = 10⁶` integers, in any order. Name an approach that beats sorting everything, and give its complexity.

**Answer:** Maintain a linked list of highest 10 elements sorted from lowest to highest. If an element is larger than the head, pop the head and insert the new element so that list remains sorted. O(10 * n) in worst case which is O(n).

> ✅ **2 / 2.** Valid. It's O(n·k), which is fine for `k = 10`. The standard tools scale better as `k` grows:
> - a **min-heap of size `k`**, `priority_queue<int, vector<int>, greater<int>>`, which is O(n log k);
> - **`nth_element`**, which is O(n) on average.

**7.7** [2] (a) Is counting sort a good fit for `n = 10⁵` values in `[0, 10⁶]`? What's the cost? (b) What about values in `[0, 10⁹]`, and what would you do instead?

**Answer:**
a. Yes `n * log(n)` for `10^5` values is `10^5 * 5 * log(10)` which is still more operations than `10^6` which would be required in counting sort. It is not the best fit for this case as it would have been if there were `10^3` elements. But even here it is a tradeoff since memory requirement is higher for counting sort than other sorting algorithms.
b. For this range, `nlogn` algorithms would beat counting sort. Best thing would be to use introsort implementation of the STL, but merge sort and quicksort with random pivot would be good too.

> 🟡 **1.5 / 2.** (b) is right. (a) gets there, but the answer contradicts itself ("yes" … "not the best fit").
> - Counting sort costs **O(n + range)**, about 1.1·10⁶ steps and a 4 MB count array. That's a clear yes.
> - For (b), a count array of 10⁹ ints would be 4 GB, so use `std::sort`. Coordinate compression is the other option, if you need the values as indices later.

---

## 8. Monotonic stack and encoding

**8.1** [2] For `[3, 1, 4, 1, 5, 9, 2, 6]`, give the nearest value **to the left that is `<=`** each element (`-1` if none).

**Answer:** `[-1, -1, 3, 1, 1, 5, 1, 2]`

> 🟡 **1.5 / 2.** Correct: `[-1, -1, 1, 1, 1, 5, 1, 2]`. For `4` at index 2, the **nearest** value on the left that's `<= 4` is the `1` right next to it, not the `3`. The `3` was popped when `1` arrived, which is exactly why it can never be an answer again.

**8.2** [1] What do you change to get the nearest **strictly greater** value **to the right** instead?

**Answer:** Right to left traversal and keep a monotonic strictly decreasing from bottom to top stack. Pop until less than current or empty. Decide and push

> ✅ **1 / 1.** Right direction and right invariant. The pop condition is worded backwards, though. You pop **while the top is `<=` current**, i.e. until the top is **greater** than the current value, or the stack is empty.

**8.3** [2] (a) Decode `"3#a#b0#2#12"` using the `len#str` format. (b) Why can't a plain `,` delimiter handle `["a,b", "c"]`?

**Answer:** 
a.`["a#b", "", "12"]`
b. Because it would fail to consider "a,b" as a single input.

> ✅ **2 / 2.** `"a,b,c"` decodes as `["a", "b", "c"]`.

---

## 9. C++

**9.1** [1] What's wrong here?

```cpp
int a = 100000, b = 100000;
long long c = a * b;
```

- A. Nothing, `c` is 10¹⁰
- B. `a * b` is computed in `int` and overflows before it's widened
- C. Compile error
- D. `c` is rounded to the nearest `int`

**Answer:** A assuming `int` in the system is big enough

> ❌ **0 / 1.** Correct: **B.**
> - `int` is 32-bit on every judge you'll use (max ≈ 2.1·10⁹).
> - The type of `a * b` comes from its **operands**, not from the variable it's assigned to. So it overflows in `int` (UB) before being widened.
> - Fix it with `1LL * a * b` or `(long long)a * b`.
> - This is one of the most common wrong-answer causes in contests.

**9.2** [2] What happens when `v` is empty, and how do you fix it?

```cpp
for (int i = 0; i < v.size() - 1; i++) { ... }
```

**Answer:** dunno

> ❌ **0 / 2.**
> - `v.size()` returns `size_t`, which is **unsigned**. So `0 - 1` wraps to 2⁶⁴ − 1, the condition is true, and the loop body reads `v[0]`, `v[1]`, … out of bounds (UB, usually a crash).
> - Fix it with `i + 1 < v.size()`, or `(int)v.size() - 1`.
> - Your `quickSort(a, 0, a.size() - 1)` call has the same trap on an empty array.

**9.3** [1] After `vector<int> b = std::move(a);`, which are guaranteed safe? *(select all)*

- A. `a.size()`
- B. `a[0]`
- C. `a.clear()`
- D. `a = {1, 2};`

**Answer:** A, C, D

> ✅ **1 / 1.**

**9.4** [2] In a chaining HashMap, `put` on an existing key doesn't update the value. Find the bug.

```cpp
for (auto p : buckets[idx])
    if (p.first == key) { p.second = value; return; }
```

**Answer:** `auto p: ...` creates a copy of pair. Fix would be to use the reference `auto& p: ...`

> ✅ **2 / 2.**

**9.5** [1] `void f(vector<int>& v);` is called as `f({1, 2, 3});`. Does it compile? Why or why not?

**Answer:** No, because `{1, 2, 3}` is a temporary val and would require a `const`  declaration in function `f`.

> ✅ **1 / 1.** A temporary (an rvalue) can't bind to a non-const lvalue reference. `const vector<int>&`, taking it by value, or `vector<int>&&` would all accept it.

**9.6** [1] You push `3, 1, 4` into a `priority_queue<int>`. What is `top()`? Write the declaration of a **min**-heap of `int`.

**Answer:** no idea

> ❌ **0 / 1.**
> - `top()` is **4**, because `priority_queue` is a **max**-heap by default.
> - A min-heap is `priority_queue<int, vector<int>, greater<int>> pq;`.
> - For pairs, the same `greater<>` gives you the smallest `.first`, and you'll use that all the time in Dijkstra.

**9.7** [1] After `ios::sync_with_stdio(false); cin.tie(nullptr);`, which are true? *(select all)*

- A. `cin` can no longer read numbers
- B. Mixing `printf` and `cout` can print in the wrong order
- C. It only affects file I/O
- D. In an interactive problem, you must flush output yourself before reading the reply

**Answer:**

> ❌ **0 / 1.** Correct: **B, D.**
> - `sync_with_stdio(false)` gives C++ streams their own buffer, separate from C's `stdio`. That's why it's fast, and also why mixing `printf`/`cout` can come out in the wrong order.
> - `cin.tie(nullptr)` stops `cin` from flushing `cout` before every read. In interactive problems you then need `cout << endl` or `cout.flush()` after each query.

**9.8** [1] `abs(INT_MIN)` is:

- A. `INT_MAX + 1`
- B. `INT_MIN`
- C. Undefined behaviour
- D. `0`

**Answer:**

> ❌ **0 / 1.** Correct: **C.** `-INT_MIN` doesn't fit in `int` (the range is `[-2³¹, 2³¹ − 1]`), so it's signed overflow. In practice it usually gives back `INT_MIN`, which is still negative. Your notes on First Missing Positive mention this.

---

## 10. Contest-style problems

For each one, give the **approach**, the **time complexity**, and any **pitfalls** (types, edge cases). Pseudocode is fine.

**P1** [3] `n ≤ 2·10⁵`, `|a_i| ≤ 10⁹`. Count the pairs `i < j` with `a_i + a_j = k`.

**Answer:** 
Implementation ->
Keep an unordered map, with `{val: count of occurence}`. For each current num check how many occurences exist for `k - a_i` and add it to total pair count. Then increase the count for current element in the map. Return the total count at end.

Compl -> O(n) time and O(n) memory

Pitfall -> Adding the current element before and then checking the existence of `k - a_i` as this would fail when `2 * a_i = k`.
Another would be to check the bounds of integer.

> 🟡 **2.5 / 3.** Correct approach and order. "Check the bounds of integer" is too vague to count as the main pitfall.
> - The **answer** can be up to `n(n-1)/2 ≈ 2·10¹⁰`, e.g. all equal values with `k = 2a`. That needs `long long`.
> - `k - a_i` can also overflow `int` if `|k|` is up to 2·10⁹.

**P2** ★ [3] `n ≤ 2·10⁵`. Count the pairs `i < j` with `a_j - a_i = j - i`.

**Answer:**
`a_j - j = -(a_i - i)`
Implementation ->
Keep an unordered map, with `{a_i - i: count of occurences}`. For each current num check how many occurences exist for `-(a_i - i)` and add it to total pair count. Then increase the count for current element in the map. Return the total count at end.

Compl -> O(n) time and O(n) memory

Pitfall -> Adding the current element before and then checking the existence of `-(a_i - i)` as this would always be true if the first element is `0`.
Another would be to check the bounds of integer.

> 🟡 **1.5 / 3.** The key idea is right: rewrite the condition so each side depends on one index only, then count matches with a map.
> - The algebra has a sign slip. `a_j - a_i = j - i` ⇒ `a_j - j = a_i - i`, so you look up the **same** value `a_j - j`, not its negation.
> - As written, `[1, 2, 3]` gives 0 instead of 3.
> - The same `long long` point as P1 applies to the count.

**P3** [3] `n, q ≤ 2·10⁵`, `|a_i| ≤ 10⁹`. Each query `(l, r)` asks for two things: the sum of `a[l..r]`, and how many **even** numbers are in `a[l..r]`.

**Answer:**

Implementation ->
We traverse the array once and store 2 prefix arrays. One for sum, and one for count of even numbers. We use them to calculate the sum and even number count in O(1) time.

Compl -> O(n + q) time and O(n) memory

Pitfall -> One pitfall would be to match the query inclusion and exclusion for (l, r).
The value of elements are big so would be better to use `long long` to store the prefix sums.

> ✅ **3 / 3.** One more trap worth knowing: test parity with `a % 2 == 0`, not `a % 2 == 1`. The second fails for negative odd numbers, because `-3 % 2 == -1`.

**P4** [3] An array of `n` integers, each in `[1, n]`. Every value appears once or twice. Return all the values that appear twice, in O(n) time and O(1) extra space (the output doesn't count).

**Answer:**
Implementation ->
Mark each element's `i-1` position as negative.
If already negative, add to result array.

Compl -> O(n) time and O(1) memory

Pitfall -> While checking the current elements correct marking, use `abs` to convert from negative to not go out of bounds.

> ✅ **3 / 3.** Cyclic sort also works: after placing, any `i` with `nums[i] != i + 1` holds a duplicate.

**P5** [3] `n ≤ 2·10⁵` lowercase strings, each of length `≤ 20`. Count the pairs `i < j` where `s_i` and `s_j` are anagrams.

**Answer:**
Implementation ->
Keep a `unordered_map<string, int>` which stores the sorted anagram as key and count as value.
Traverse and sort each array's copy or itself if input change is allowed, and check for key in map.
Increase the total and them add it or increment the count in map.

Compl -> O(n slogs)  where s is string length time and O(n * s) memory

Pitfall -> Same pitfall, be careful to only add the key to map after checking the anagrams.

> 🟡 **2.5 / 3.** Correct.
> - The missed pitfall is the `long long` total again: all `2·10⁵` strings could be anagrams of each other, giving about 2·10¹⁰ pairs.
> - Alternatively, count each group's size and add `c·(c-1)/2` at the end.

---

## Assessment notes for future quizzes

*Quiz 1, 2026-10-17: 82/103. About 92/103 without the slips.*

### Gaps to retest
These are missing knowledge or missing habits. Retest each one in a later quiz with a **new question**, not the same one reworded.

| Gap | Seen in | How to retest |
|---|---|---|
| `size()` is unsigned, so `size() - 1` wraps on an empty vector | 9.2 (blank) | Loops like `i < v.size() - k`, or `int` vs `size_t` comparisons on small or empty vectors |
| The type of an expression comes from its operands (`int * int` overflows before widening) | 9.1 | `a * b`, `a + b` near 2·10⁹, sums of `n` values up to 10⁹ |
| Using `long long` for counts and sums out of habit | P1, P2, P5 | Every contest-style problem asks for the **answer type** explicitly |
| `priority_queue`: max-heap by default, min-heap syntax, ordering of pairs | 9.6 (blank) | Top-k with a heap, "smallest `.first` first" with pairs |
| Fast I/O side effects (`printf` mixing, flushing in interactive problems) | 9.7 (blank) | Select-all on I/O behaviour |
| Signed overflow is UB (`abs(INT_MIN)`, `INT_MIN + x`) | 9.8 (blank), 4.3 | Sentinels, negation, `abs` |
| Anti-hash hacks and a seeded custom hash | 2.7 | Ask them to write a `custom_hash` (splitmix64 + time seed) |
| Sign marking: a `0` slot can't hold a mark | 6.4 | Another sign-marking problem (e.g. Find All Missing Numbers) |
| Kadane: start from `nums[0]` instead of a sentinel | 4.2, 4.3 | Variants with different initial values |
| Using hints like "sorted" to cut space or time | 6.6 | Problems on sorted input (two pointers, dedupe, pair sum) |
| Monotonic stack: pop condition and "nearest" vs "first" | 8.1, 8.2 | Trace nearest greater to the right, previous smaller element |

### Slip patterns
The knowledge was there and the execution went wrong. Design questions that catch these:
- **Mental arithmetic in traces** (4.4, 3.1, 8.1). Include traces with 6–10 steps, and ask for the intermediate state, not just the final answer.
- **Multi-part questions half answered** (3.2, 4.2, 3.6). Keep using (a)/(b)/(c) parts. Give zero for a part that's missing.
- **Algebra when rewriting a condition** (P2). Include another "rewrite so each side depends on one index" problem.
- **Complexity estimate at the limits** (1.1). Include a constraints → complexity question every quiz.
- **Counterexamples that don't actually break the code** (1.4, 2.3). Ask for the input **and** what the code does on it.

### Solid
Low priority to retest. A single quick question is enough:
- `unordered_map::operator[]` inserting, insert/lookup order (Two Sum)
- Prefix sums: 1D, 2D, longest subarray, divisible by `m`, ±1 reduction, difference array
- Boyer-Moore, including `n/k` and the verification pass
- Cyclic sort and First Missing Positive range
- Dutch national flag, sorting stability and complexities, quick sort on duplicates
- Length-prefix encoding
- `auto` vs `auto&`, binding temporaries, moved-from state

### Plan for the next quiz
- About 20–25% of the questions from **Gaps to retest**, mixed in with the new topic.
- Every contest-style problem asks for approach, complexity, **answer type** and one edge case.
- At least one "build a worst-case input" question and one trace that asks for intermediate state.
