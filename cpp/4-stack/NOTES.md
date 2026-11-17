# Stack — Notes

The concepts come first, for a quick revision. The problem-by-problem notes are at the end, for when you want more detail.

# Concepts

## Matching pairs with a stack (brackets)
- "Every opener is closed by the same type, in the right order" means the **most recent unclosed opener** must match each closer. Most recent first is LIFO, so use a stack.
- Push openers. On a closer: if the stack is **empty**, or the top isn't the matching opener, return `false`; otherwise pop.
- At the end, return `st.empty()`: leftover openers (`"(("`) are unclosed.
- Check `empty()` before `top()`: `top()` on an empty `std::stack` is undefined behaviour, not an exception. `")"` is the test for it.
- A close → open map (`{')', '('}, ...}`) replaces the two helper functions if you prefer one lookup.
- O(n) time, O(n) space.

## `std::stack` API
- `push`, `top` (a reference, doesn't remove), `pop` (returns `void`: read `top()` first), `empty`, `size`. No iterators, no `clear()`.
- A `vector` works as a stack too (`push_back`, `back`, `pop_back`) and can also be indexed and iterated.

# Problems

| # | Problem | File | Approach | Time | Space |
|---|---------|------|----------|------|-------|
| 1 | Valid Parentheses | [valid_parentheses.cpp](valid_parentheses.cpp) | Push openers; on a closer, fail if the stack is empty or the top doesn't match, else pop; valid if the stack ends empty | O(n) | O(n) |

Harnesses are skipped while preparing for the interview. Solutions are checked on the NeetCode IDE instead.

### 1. Valid Parentheses
- Solved in the NeetCode IDE, correct.
- Checks `st.empty()` before `st.top()`, so `")"` is handled. Returns `st.empty()`, so `"(("` is handled.
- `for (char& c : s)` only reads `c`: use `char c` (a reference to a `char` saves nothing).
