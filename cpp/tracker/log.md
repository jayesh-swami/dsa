# Daily log

One entry per practice day, newest first. Links point to the quiz files, the problem rows in [problems.csv](problems.csv) and the notes. Strength and review dates live in [concepts.csv](concepts.csv); this is only a record of what was done.

## 2026-11-12

- **Contest:** Codeforces Round 1134 (Div. 4), [contest folder](../../contests/codeforces/2290-round_1134_div4/). A, B, C, E accepted in the contest. Then upsolved D and F with hints.
- **Problems:**

  | id | Problem | Outcome |
  |---|---|---|
  | CF2290A | Three Piles | Accepted in contest |
  | CF2290B | Stubborn Pen | Accepted in contest |
  | CF2290C | Books on a Shelf | Accepted in contest |
  | CF2290D | Letters Down | Upsolved with hints (union of half-open letter ranges); marked to redo |
  | CF2290E | Avalanche | Accepted in contest |
  | CF2290F | Value Counters | Upsolved with hints (`pos_x = b_x + n - x`), accepted; marked to redo |
  | CF2290G | Lakeside Trail | Unfinished in contest; upsolve pending |

- **New or changed concepts:**
  - `interval-union-small-alphabet` (weak)
  - `count-split-identity` (weak)
  - Evidence added to `cpp-fast-io` (left out in D and E), `answer-all-parts` (F, hint 3) and `cpp-vector-vs-list` (C).
- **Takeaways:**
  - Contest problems from C onward reward one key observation more than a known pattern. Keep interview-style problems as the main track and do about one contest a week, upsolving one or two past the last solved.
  - My first idea for D and F was a graph or topo sort; both were counting arguments.
- **Next:**
  - Upsolve G1/G2.
  - Redo D and F from scratch in 2 days.

## 2026-11-05

- **Quiz:** [Q02 sliding-window flashcards](../quizzes/flashcards/q02_2026-11-05.md): 7.5 / 11, with the coding question SW02 (Maximum Average Subarray I) correct first time. Missed: the second part of two questions (`answer-all-parts`), and picked a prefix-sum problem as a window.
- **Revised:**
  - Quick notes on all weak and shaky concepts.
  - How to trace code in an interview: say the expected output first, keep a value history for each variable, read the code literally.
- **Problems:**

  | id | Problem | Time | Outcome |
  |---|---|---|---|
  | SW04 | Longest Substring Without Repeating Characters | 20 min | Solved alone (set version); jump version learned |
  | SW05 | Longest Repeating Character Replacement | 50 min, then a second attempt | Not optimal; O(n) running `maxf` learned; marked to redo |
  | SW06 | Permutation in String | under 20 min | Solved alone, then also wrote the O(n) `matches` counter version |

- **New or changed concepts:**
  - `sw-validity-count` (weak)
  - `sw-fixed-count` (untested)
  - `read-the-signature` (shaky)
  - `trace-literally` (shaky): from now on, every quiz has a trace card for it.
- **Process:** set the daily routine. Cold flashcard quiz first, then revise only the misses, a due redo, 2–3 new problems done like an interview, then log.
- **Next:**
  - A quiz that includes the first trace card.
  - Redo SW05 on 2026-11-07.
  - Max Consecutive Ones III (LC 1004).

## 2026-11-04

*(Before the log started; from the tracker.)*
- **Problems:**
  - SW01 Contains Duplicate II (15 min, not optimal; set version learned).
  - SW03 Best Time to Buy and Sell Stock (8 min, solved alone).
- **Process:**
  - Long quizzes were replaced by flashcards.
  - The tracker was created.
