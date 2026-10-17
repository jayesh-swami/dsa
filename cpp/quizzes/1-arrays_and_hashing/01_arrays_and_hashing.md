# Quiz 1: Arrays & Hashing

**How to take it**
- Write your answer under each question, after **Answer:**.
- For multiple choice, write the letter. If a question says *select all*, more than one letter may be correct.
- Keep free-text answers short: a sentence or two, a formula, or a few lines of code or pseudocode.
- No compiler and no notes. Aim for about 90 minutes.
- ★ marks a **stretch** question. It builds on what you've covered and takes it one step further, the way contests and interviews usually do. Attempt it anyway: a partial idea still gets credit.
- Points are in brackets. **Total: 103.** When you're done, ask me to grade it.

---

## 1. Complexity and constraints

**1.1** [1] A judge runs about 10⁸ simple operations per second. Here `n ≤ 2·10⁵` and the time limit is 1 s. Which complexities fit comfortably? *(select all)*

- A. O(n²)
- B. O(n log n)
- C. O(n)
- D. O(n log² n)

**Answer:** A,B,C

**1.2** [2] You don't know the intended solution yet, but you can read the constraints. What complexity is the setter probably hinting at for **(a)** `n ≤ 5000`, and **(b)** `n ≤ 20`?

**Answer:** O(n^2) for a and O(2^n) for b

**1.3** [2] The monotonic stack sweep has a `while` (popping) inside a `for`, but it's O(n), not O(n²). Explain why in one or two sentences.

**Answer:** Because each element will only be inserted and popped at max once from the stack.

**1.4** [2] In Longest Consecutive Sequence, a friend only counts up from `x` when `x - 1` is absent, which is correct. But they loop over the **input array** instead of the set. Describe an input where their solution becomes O(n²).

**Answer:** {1, 1, 1, 1, 1, 2, 3} Where there are multiple starts

---

## 2. Hashing

**2.1** [1] `m` is an `unordered_map<int, int>` and `x` is **not** in it. Which of these leave `m` unchanged? *(select all)*

- A. `m[x]`
- B. `m.find(x)`
- C. `m.count(x)`
- D. `m.contains(x)`
- E. `if (m[x] == 0) { ... }`

**Answer:** B, C, D

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

**2.3** [2] For Group Anagrams, someone avoids sorting by building the key from character counts. They loop over the 26 letters and append `to_string(count[c])` to the key. Give two strings that are **not** anagrams but get the same key, and say how to fix the key.

**Answer:** "aas" "bbs" would give the same key here. To fix it also add the character as part of the key.

**2.4** [2] (a) What is `-10 % 7` in C++? (b) Write an expression that always gives `x mod m` in `[0, m)`, even when `x` is negative.

**Answer:** -3. `(x % m) < 0 ? m + (x % m) : (x % m)`

**2.5** [2] A linear-probing hash set uses `h(k) = k % 7`. Its `remove` sets the slot back to `EMPTY` (no tombstones). You run `add(3)`, `add(10)`, `remove(3)`, then `contains(10)`. What does `contains(10)` return, and why? What would a tombstone change?

**Answer:** Here contains would return `false` in traditional implementation because it would check in 3rd slot and find that it is empty and stop and return `false`. Tombstone would allow it to continue its search in case it was inserted in one of the next empty slots.

**2.6** [1] Why is a prime table size usually preferred?

- A. Computing `% p` is faster for a prime `p`
- B. Keys that share a common factor with the table size would otherwise crowd into a few buckets
- C. Linear probing doesn't terminate otherwise
- D. It uses less memory

**Answer:** B

**2.7** ★ [2] On Codeforces, a solution using `unordered_map<long long, int>` passes all the pretests, but someone hacks it with a TLE. Based on what you know about how hash tables work inside, how could a specially built input cause this? Name one way to defend against it.

**Answer:** Don't know what is meant by hacking with time limit exceeded. but if you mean that they caused TLE by changing the inbuilt hashing function and caused it to create long chains instead of spreading the keys thereby reducing performance, then one way could be to not allow changing of the inbuilt hash function of unordered although I have no clue how to do that or maybe change the default hash implementation. But again this is me going off from my assumption of what hack with TLE means.

---

## 3. Prefix sums

**3.1** [1] Subarray Sum Equals K with `nums = [1, -1, 0]` and `k = 0`. How many subarrays sum to `k`?

- A. 1
- B. 2
- C. 3
- D. 4

**Answer:** C (assuming empty array is valid subarray, if not then B)

**3.2** [2] Someone forgets to seed the map with `count[0] = 1`. For `nums = [3, 4, 7]` and `k = 7`, what does their code return, and what is the correct answer? Which subarrays does the bug always miss?

**Answer:** It will miss the first subarray from left that matches the sum so in this case `[3, 4]`.

**3.3** [2] Give a concrete counterexample where a sliding window (grow right while the sum is `< k`, shrink left while it's `> k`) fails to find a subarray with sum `k`, and say why it fails.

**Answer:** The approach fails with negative numbers in an array. For eg. `[3,2,-1,7]` with `k = 4`. The algorithm would get to the window `{3,2}`, see that it is more than k and shrink it to just `{2}`, and we will miss the answer subarray which is `[3, 2, -1]`.

**3.4** [2] Now find the **longest** subarray with sum `k`. What does the map store, what do you seed it with, and why do you never overwrite an entry once it's set?

**Answer:** The map stores the first index a particular sum was seen from the left. We seed it with `mp[0] = -1` if we calculate the length as `currIndex - mp[currSum - k]`. We never overwrite because the first seen entry is bound to give us the longest possible array.

**3.5** [2] Count the subarrays whose sum is **divisible by `m`**. What do you use as the map key, and what C++ pitfall do you have to handle when the array has negatives?

**Answer:** We would use the map key as the `(prefix sum) % m` (adjusted for negative values) and the value as count. We would need to make sure that modulo always returns a positive value.

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

**3.7** [2] `P` is a zero-padded 2D prefix sum of size `(n+1) × (m+1)`, so `P[i+1][j+1]` is the sum of the rectangle from `(0, 0)` to `(i, j)`. Write the sum of the rectangle from `(r1, c1)` to `(r2, c2)` (inclusive, 0-indexed) in terms of `P`.

**Answer:** `P[r2+1][c2+1] - P[r1][c2+1] - P[r2+1][c1] + P[r1][c1];` 

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

---

## 4. Kadane and greedy

**4.1** [1] What is the maximum subarray sum of `[5, -9, 6, -2, 3]` (non-empty)?

- A. 6
- B. 7
- C. 9
- D. 5

**Answer:** B

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

**4.3** [2] Why does starting `cur` at `INT_MIN` cause trouble, and what's the cleanest way to initialise instead?

**Answer:** `cur` at `INT_MIN` causes trouble because it can overflow with negative elements when we add them to it. We can do `INT_MIN / 2` if our range allows or if empty subarrays are allowed `cur = 0`

**4.4** [2] `prices = [1, 5, 3, 8]`. (a) What's the best profit with **unlimited** transactions? (b) With **at most one** transaction? (c) In one sentence, why is the greedy for (a) correct?

**Answer:** a. 7 b. 5 c. Greedy is correct because segmentation into subproblems yield the same result as bigger subproblem. (help with wording when marking pls)

**4.5** ★ [3] Maximum **product** subarray. Why does plain Kadane (`cur = max(x, cur * x)`) fail? What extra state fixes it?

**Answer:** It fails because multiplication with negative number would not be accounted for. We can have 2 negatives giving us a big positive number but `curr * x` would become negative and would not be updated to cur (as there might be another negative ahead to make it positive). This is similar to the problem faced by sliding window solution for max subarray sum. Here the solution would be to keep another state that track the minimum subarray product and make it like `cur = max(x , max(curr * x, currMin * x))`

---

## 5. Boyer-Moore voting

**5.1** [1] Run single-candidate Boyer-Moore on `[2, 2, 1, 1, 1, 2, 2]`. What's the final candidate?

**Answer:** 2

**5.2** [1] At most how many distinct values can appear **more than `n/4`** times?

- A. 2
- B. 3
- C. 4
- D. It depends on `n`

**Answer:** B

**5.3** [2] Boyer-Moore on `[1, 2, 3]` returns `3`. What does this show, and what must you do when a majority isn't guaranteed?

**Answer:** This shows that single candidate boyer moore only works when majority is guarenteed and same count elements might fight for candidacy otherwise. We much run through the array and check the frequency of our candidate when majority is not guaranteed.

**5.4** [2] In the `n/3` version, both candidates start at `-1` and the verification pass uses two separate `if`s. What does it return for `[-1]`, and why? Give one fix.

**Answer:** `{-1, -1}`. The fix would be to do it in an if-else

---

## 6. In-place array tricks

**6.1** [1] For First Missing Positive on an array of length `n`, the answer is always in:

- A. `1..n`
- B. `0..n`
- C. `1..n+1`
- D. `1..max(nums)+1`

**Answer:** C

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

**6.3** [1] In the correct `while` version, you drop the guard `nums[nums[i] - 1] != nums[i]` (keeping the range check). What happens on `[1, 1]`?

- A. Returns 2
- B. Infinite loop
- C. Out-of-bounds access
- D. Returns 1

**Answer:** B

**6.4** [2] In the sign-marking version: (a) why replace every value `<= 0` before marking? Give both reasons. (b) Why read values with `abs()`?

**Answer:** a. The 2 reasons would be to prevent out of bounds access and to not mistakenly assume a negative number as a marked number. b. Reading value with `abs` as there might be a marked number in the array which will be negative.

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

**7.2** [2] Describe a situation where you *need* a stable sort to get the right answer.

**Answer:** An example would be sorting on multiple keys of an object, first on a then on b. In these scenarios we rely on stable sorting to maintain the order of the current elements.

**7.3** [1] In merge sort's merge, you take from the left half only when `left < right` (instead of `<=`). The result is:

- A. Still stable
- B. Sorted but no longer stable
- C. Not sorted correctly
- D. O(n²)

**Answer:** B

**7.4** [2] Quick sort with a **random** pivot and Lomuto partition (`<` comparison) on an array of 10⁵ equal values. What's the complexity, why, and what fixes it?

**Answer:** O(n ^ 2) because each time the partition length would be `1` and `p-1` starting from n. We can fix this by doing a 3 way partition of less than, equals and more than.

**7.5** [2] Every element is at most 3 positions away from its sorted position. Among bubble, selection, insertion and merge sort, which is the best choice, and what's its complexity here?

**Answer:** Insertion sort as it would be max 3 swaps per element. O(3 *n)

**7.6** [2] You need the 10 **largest values** from `n = 10⁶` integers, in any order. Name an approach that beats sorting everything, and give its complexity.

**Answer:** Maintain a linked list of highest 10 elements sorted from lowest to highest. If an element is larger than the head, pop the head and insert the new element so that list remains sorted. O(10 * n) in worst case which is O(n).

**7.7** [2] (a) Is counting sort a good fit for `n = 10⁵` values in `[0, 10⁶]`? What's the cost? (b) What about values in `[0, 10⁹]`, and what would you do instead?

**Answer:**
a. Yes `n * log(n)` for `10^5` values is `10^5 * 5 * log(10)` which is still more operations than `10^6` which would be required in counting sort. It is not the best fit for this case as it would have been if there were `10^3` elements. But even here it is a tradeoff since memory requirement is higher for counting sort than other sorting algorithms.
b. For this range, `nlogn` algorithms would beat counting sort. Best thing would be to use introsort implementation of the STL, but merge sort and quicksort with random pivot would be good too.

---

## 8. Monotonic stack and encoding

**8.1** [2] For `[3, 1, 4, 1, 5, 9, 2, 6]`, give the nearest value **to the left that is `<=`** each element (`-1` if none).

**Answer:** `[-1, -1, 3, 1, 1, 5, 1, 2]`

**8.2** [1] What do you change to get the nearest **strictly greater** value **to the right** instead?

**Answer:** Right to left traversal and keep a monotonic strictly decreasing from bottom to top stack. Pop until less than current or empty. Decide and push

**8.3** [2] (a) Decode `"3#a#b0#2#12"` using the `len#str` format. (b) Why can't a plain `,` delimiter handle `["a,b", "c"]`?

**Answer:** 
a.`["a#b", "", "12"]`
b. Because it would fail to consider "a,b" as a single input.

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

**9.2** [2] What happens when `v` is empty, and how do you fix it?

```cpp
for (int i = 0; i < v.size() - 1; i++) { ... }
```

**Answer:** dunno

**9.3** [1] After `vector<int> b = std::move(a);`, which are guaranteed safe? *(select all)*

- A. `a.size()`
- B. `a[0]`
- C. `a.clear()`
- D. `a = {1, 2};`

**Answer:** A, C, D

**9.4** [2] In a chaining HashMap, `put` on an existing key doesn't update the value. Find the bug.

```cpp
for (auto p : buckets[idx])
    if (p.first == key) { p.second = value; return; }
```

**Answer:** `auto p: ...` creates a copy of pair. Fix would be to use the reference `auto& p: ...`

**9.5** [1] `void f(vector<int>& v);` is called as `f({1, 2, 3});`. Does it compile? Why or why not?

**Answer:** No, because `{1, 2, 3}` is a temporary val and would require a `const`  declaration in function `f`.

**9.6** [1] You push `3, 1, 4` into a `priority_queue<int>`. What is `top()`? Write the declaration of a **min**-heap of `int`.

**Answer:** no idea

**9.7** [1] After `ios::sync_with_stdio(false); cin.tie(nullptr);`, which are true? *(select all)*

- A. `cin` can no longer read numbers
- B. Mixing `printf` and `cout` can print in the wrong order
- C. It only affects file I/O
- D. In an interactive problem, you must flush output yourself before reading the reply

**Answer:**

**9.8** [1] `abs(INT_MIN)` is:

- A. `INT_MAX + 1`
- B. `INT_MIN`
- C. Undefined behaviour
- D. `0`

**Answer:**

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

**P2** ★ [3] `n ≤ 2·10⁵`. Count the pairs `i < j` with `a_j - a_i = j - i`.

**Answer:**
`a_j - j = -(a_i - i)`
Implementation ->
Keep an unordered map, with `{a_i - i: count of occurences}`. For each current num check how many occurences exist for `-(a_i - i)` and add it to total pair count. Then increase the count for current element in the map. Return the total count at end.

Compl -> O(n) time and O(n) memory

Pitfall -> Adding the current element before and then checking the existence of `-(a_i - i)` as this would always be true if the first element is `0`.
Another would be to check the bounds of integer.


**P3** [3] `n, q ≤ 2·10⁵`, `|a_i| ≤ 10⁹`. Each query `(l, r)` asks for two things: the sum of `a[l..r]`, and how many **even** numbers are in `a[l..r]`.

**Answer:**

Implementation ->
We traverse the array once and store 2 prefix arrays. One for sum, and one for count of even numbers. We use them to calculate the sum and even number count in O(1) time.

Compl -> O(n + q) time and O(n) memory

Pitfall -> One pitfall would be to match the query inclusion and exclusion for (l, r).
The value of elements are big so would be better to use `long long` to store the prefix sums.

**P4** [3] An array of `n` integers, each in `[1, n]`. Every value appears once or twice. Return all the values that appear twice, in O(n) time and O(1) extra space (the output doesn't count).

**Answer:**
Implementation ->
Mark each element's `i-1` position as negative.
If already negative, add to result array.

Compl -> O(n) time and O(1) memory

Pitfall -> While checking the current elements correct marking, use `abs` to convert from negative to not go out of bounds.

**P5** [3] `n ≤ 2·10⁵` lowercase strings, each of length `≤ 20`. Count the pairs `i < j` where `s_i` and `s_j` are anagrams.

**Answer:**
Implementation ->
Keep a `unordered_map<string, int>` which stores the sorted anagram as key and count as value.
Traverse and sort each array's copy or itself if input change is allowed, and check for key in map.
Increase the total and them add it or increment the count in map.

Compl -> O(n slogs)  where s is string length time and O(n * s) memory

Pitfall -> Same pitfall, be careful to only add the key to map after checking the anagrams.
