# Linked List — Notes

The concepts come first, for a quick revision. The problem-by-problem notes are at the end, for when you want more detail.

# Concepts

## Reverse a list in place
- Three pointers: `prev` (the reversed part, starts `nullptr`), `curr` (the next node to flip), `next` (saved so the rest isn't lost).
- Each step: save `next = curr->next`, flip `curr->next = prev`, then move both forward (`prev = curr`, `curr = next`). Return `prev`, the new head.
- The empty list falls out for free: the loop doesn't run and `prev` is `nullptr`.
- O(n) time, O(1) space.
- **Recursive:** base case `!head || !head->next` → return `head`. Otherwise `rev = reverseList(head->next)`; the old `head->next` is now the **tail** of the reversed part, so `head->next->next = head` attaches `head` in O(1) (no walk to the end), and `head->next = nullptr` ends the list (forget it and you get a 2-node cycle). Return `rev` unchanged at every level. O(n) stack space, so the iterative one is the default; a very long list could overflow the call stack.

## Dummy head (merging, building a new list)
- Start with `ListNode dummy;` and `ListNode* tail = &dummy;`. Append with `tail->next = node; tail = tail->next;`, return `dummy.next`. No special case for "which node becomes the head", and an empty result just returns `nullptr`.
- The dummy can live on the stack: you return `dummy.next` (a real node), never `&dummy`. With `new` it would leak unless deleted.
- **Leftovers in a merge:** when one list runs out, the rest of the other is already linked and sorted, so attach it in O(1): `tail->next = list1 ? list1 : list2;`. No loop needed.
- Ties: `<=` takes from `list1` first (stable). It doesn't matter for ints, but it does when nodes carry other data.

## Fast and slow pointers (Floyd's cycle detection)
- `slow` moves 1 step, `fast` moves 2. No cycle: `fast` hits `nullptr`, so return `false`. Cycle: they meet, so return `true`. O(n) time, O(1) space (a set of visited nodes is O(n) space).
- **Why they must meet:** once both are inside the cycle, each step the gap from `fast` to `slow` (going forward) shrinks by exactly 1, since fast gains 1 per step. A gap shrinking by 1 can't skip over 0, so they meet within one lap (at most cycle-length steps).
- **Why speed 2 and not 3:** with speed 3 the gap shrinks by 2 per step (mod the cycle length k). If k is even and the gap is odd, it stays odd and never hits 0, so they can dodge each other forever (a 2-node cycle `A ⇄ B`, slow on A, fast on B: they swap every step). In general they meet only if `gcd(b − a, k)` divides the starting gap; speeds 1 and 2 give `b − a = 1`, which always works.
- Loop condition: `while (fast && fast->next)`. That's all you need to guard: `fast->next->next` may be `nullptr`, which just ends the loop on the next check. `slow` is behind `fast`, so it can't be null first.
- Same tool: the middle of a list (when `fast` reaches the end, `slow` is in the middle), used in Reorder List and Palindrome Linked List.

## Split, reverse, merge (Reorder List)
- `L0 → Ln → L1 → Ln-1 …` = first half interleaved with the **reversed** second half. Three building blocks: find the middle, reverse the second half, merge alternately.
- **Middle with fast and slow:** start `slow = head, fast = head->next`; `while (fast && fast->next)`. Then `slow` is the end of the first half (the first half gets the extra node when n is odd). Cut with `second = slow->next; slow->next = nullptr;`. One pass, no length count.
- **Alternate merge without a dummy:** the first half is never shorter, so loop on the second half:
  ```cpp
  while (second) {
      ListNode* n1 = first->next; ListNode* n2 = second->next;
      first->next = second; second->next = n1;
      first = n1; second = n2;
  }
  ```
- O(n) time, O(1) space. (Copying the nodes into a vector and relinking with two pointers is the O(n)-space version.)

## Gap of n between two pointers (n-th from the end)
- To reach the n-th node from the end in one pass: move `fast` n steps ahead, then move both until `fast` falls off. `slow` is then n nodes behind the end.
- To **remove** it you need the node before it, so start `slow` on a dummy before `head` (gap n + 1). The dummy also covers removing the head.

## Merge k sorted lists
- **One by one** into a running result: the i-th merge walks about `i·n` nodes, so O(nk²) = O(N·k) for N = nk total. The early nodes are re-walked k times.
- **Min-heap of the k current heads:** pop the smallest, append it, push its `next`. Each node is pushed and popped once and the heap never holds more than k: **O(N log k)** time, O(k) space.
  ```cpp
  priority_queue<pair<int, ListNode*>, vector<pair<int, ListNode*>>, greater<>> pq;  // min-heap
  ```
  `priority_queue` is a max-heap by default; `greater<>` flips it. On equal values `pair` compares the pointers next, which is harmless. Push only non-null heads (`[[]]`).
- **Divide and conquer:** merge pairs in rounds (`lists[i]` with `lists[i + step]`), like merge sort: log k rounds, each touching N nodes, so O(N log k) time and O(1) extra space when done in a loop.

## Creating objects
- Stack: `ListNode a;`, `ListNode b(5);`, `ListNode c{5};`. Use `.`; freed at the end of the scope; never return its address.
- Heap: `ListNode* p = new ListNode(5);`. Use `->`; lives until `delete p`. Real code: `std::make_unique<ListNode>(5)`.
- `ListNode a();` declares a function, not an object (most vexing parse). Write `ListNode a;` or `ListNode a{};`.

## `.` vs `->`
- `.` is for an object, `->` is for a pointer. `p->next` is shorthand for `(*p).next`.
- Look at the declaration: `ListNode* curr` → `curr->next`. A node owned directly (`ListNode dummy;`) → `dummy.next`.
- `*p.next` parses as `*(p.next)` because `.` binds tighter than `*`. Write `(*p).next`, or just `p->next`.

# Problems

| # | Problem | File | Approach | Time | Space |
|---|---------|------|----------|------|-------|
| 1 | Reverse Linked List | [reverse_linked_list.cpp](reverse_linked_list.cpp) | `prev` / `curr` / `next`: save next, flip `curr->next`, advance both; return `prev`. (Also recursive: `head->next->next = head`) | O(n) | O(1) (recursive: O(n)) |
| 2 | Merge Two Sorted Lists | [merge_two_sorted_lists.cpp](merge_two_sorted_lists.cpp) | Dummy head and a tail pointer; take the smaller head each step; attach what's left | O(n + m) | O(1) |
| 3 | Linked List Cycle | [linked_list_cycle.cpp](linked_list_cycle.cpp) | Fast (2 steps) and slow (1 step) pointers; they meet only if there's a cycle | O(n) | O(1) |
| 4 | Reorder List | [reorder_list.cpp](reorder_list.cpp) | Fast and slow to the middle, cut after `slow`, reverse the second half, merge alternately with a dummy head | O(n) | O(1) |
| 5 | Remove Nth Node From End of List | [remove_nth_node_from_end.cpp](remove_nth_node_from_end.cpp) | Dummy head; `fast` starts `n` ahead, move both until `fast` is null, so `slow` stops before the target; unlink. (Also two passes: length, then `len - n` steps) | O(n) | O(1) |
| 6 | Merge k Sorted Lists | [merge_k_sorted_lists.cpp](merge_k_sorted_lists.cpp) | Min-heap of `{val, node}` for the current heads; pop the smallest, append, push its `next` | O(N log k) | O(k) |

Harnesses are skipped while preparing for the interview. Solutions are checked on the NeetCode IDE instead.

### 1. Reverse Linked List
- Iterative: 2 minutes, correct.
- Recursive (`reverseListRecursive`, the follow-up): correct, after asking whether each level has to find the last node (it doesn't: it's `head->next`). The two base-case `if`s can be one: `if (!head || !head->next) return head;`.
- First attempt wrote `curr.next` on a `ListNode*`; see [`.` vs `->`](#-vs--).
- `next = head` in the declaration is overwritten before it's read; `ListNode* next` inside the loop is enough.

### 2. Merge Two Sorted Lists
- Solved in the NeetCode IDE, correct. Dummy head on the stack, returns `dummy.next`.
- First version attached the leftover list with two `while` loops, one node at a time. Rewritten: the leftover is already linked, so one assignment attaches it in O(1). Also switched to `<=` (stable: `list1` first on ties).

### 3. Linked List Cycle
- Solved in the NeetCode IDE, correct (Floyd's fast and slow pointers).
- The guards can be simpler: `while (fast && fast->next)` covers everything. `slowptr` can't be null before `fastptr`, and checking `fastptr->next->next` ahead of time isn't needed.

### 4. Reorder List
- Solved in the NeetCode IDE, correct. Found the split / reverse / merge decomposition alone and reused the reverse and dummy-head code from earlier.
- Odd and even lengths both work: `skips = ⌈n/2⌉`, so the first half keeps the middle node, and `n = 1` gives an empty second half.
- First version found the middle by counting the length (an extra pass). Rewritten with fast and slow pointers, both starting at `head`, and cut after `slow`.
  - With `fast = head`, an even length leaves `slow` one past the true middle: `[1,2,3,4]` splits as `[1,2,3]` + `[4]`. Still correct, because `zip` attaches the leftover. Starting `fast = head->next` gives the balanced split `[1,2]` + `[3,4]`. Know which node each start gives.
  - Checked: n = 1, 2, 4, 5 all give the right order.
- `zip` with a dummy head and an `i % 2` counter works; swapping the links pairwise (no dummy, no counter) is shorter.

### 5. Remove Nth Node From End of List
- Solved in the NeetCode IDE. Two-pass version (`removeNthFromEndTwoPass`) alone, correct. The dummy head makes removing the head (`[1], n = 1`) work with no special case.
- `curr` and `next` are carried along but only `prev` is needed: `prev->next = prev->next->next;`.
- The removed node isn't `delete`d. Fine on LeetCode; in real code it's a leak.
- **One pass (`removeNthFromEnd`)**, after guiding questions: `slow` on the dummy, `fast` on `head` moved `n` steps, then both move until `fast` is null. The gap is `n + 1`, so `slow` stops on the node **before** the target. Correct, including `[1], n = 1` (slow stays on the dummy).
  - `prev` / `curr` / `next` just to unlink: `s->next = s->next->next;` is the same.

### 6. Merge k Sorted Lists
- Solved in the NeetCode IDE, correct. All three approaches' complexities stated correctly before coding (one by one O(nk²), heap and divide and conquer O(N log k)). The `greater<>` declaration was shown before coding.
- `if (p.second)` is always true: only non-null nodes are ever pushed.
- `auto [val, node] = pq.top();` (structured binding) reads more clearly than `p.second` three times.
- The last node's `next` is already `nullptr`: if it had a successor, that would have been pushed and popped after it.
- Divide and conquer not written yet; worth doing as practice (it reuses `mergeTwoLists`).
