# Practice tracker

Three CSV tables track what I've practised and where I'm weak. GitHub shows them as tables.

| File | One row per | What it answers |
|---|---|---|
| [concepts.csv](concepts.csv) | Concept (a pattern, technique or C++ point) | How strong am I on it, when did I last practise it, when is it due again |
| [problems.csv](problems.csv) | Problem solved | Which concepts it uses, how long it took, whether I found the approach myself |
| [quizzes.csv](quizzes.csv) | Quiz | Which concepts it tested, and which I got right, partly right or wrong |
| [log.md](log.md) | Practice day | What I did that day: quiz, concepts revised, problems, what's next |

`concepts` is a `;`-separated list of concept ids in both `problems.csv` and `quizzes.csv`.

## Columns

**concepts.csv**
- `strength`: `weak` (wrong or blank in a quiz, or couldn't solve without the solution) · `shaky` (partly right, slips) · `solid` (right) · `untested` (practised in problems, not quizzed yet)
- `last_practiced`: the latest problem or quiz that used it. Computed by the script.
- `next_review`: `last_practiced` plus 2 days (weak), 5 (shaky) or 14 (solid). Untested concepts are due right away. Computed by the script.
- `evidence`: why it has its current strength (quiz question numbers, problem ids).

**problems.csv**
- `date`: the day the problem was solved (from git for older problems).
- `minutes`: time to a working solution.
- `outcome`: `solo` (optimal approach found alone) · `suboptimal` (solved alone, but not optimally) · `hint` (needed a hint) · `learned` (read the solution) · `unknown` (before tracking started)
- `revisit`: `yes` if it's worth redoing from scratch.

**quizzes.csv**
- `type`: `flashcards` (quick concept check) or `full` (long topic quiz, used only for Q01).
- `problem`: the coding question included in the quiz, if there was one.
- `correct` / `partial` / `wrong`: concept ids, by how they went in this quiz.

## Flashcard quizzes

- About 10 cards, each a one-line question with a one-line answer (definitions, "which pattern?", complexities, C++ gotchas), taking 5–10 minutes. Sometimes one coding question goes in between the cards. They live in `cpp/quizzes/flashcards/`, named `qNN_YYYY-MM-DD.md`.
- Cards come from `python3 tracker.py due`, weakest first, plus the topic in progress.
- **Every quiz has at least one trace card** (`trace-literally`): a small algorithm of 5–15 lines with concrete input, where the answer is the exact output or the final values. Pick code where intent and arithmetic differ: off-by-one bounds, `i - k` indices, integer division, a `max` that doesn't fire, unsigned `size()`, a stale counter. Do it on paper, line by line, without running it.
- Grading goes inline in the same file: a score summary at the top, and a ✅ / 🟡 / ❌ note under each answer.
- After grading:
  1. Add a row to `quizzes.csv`.
  2. Update each tested concept's `strength`: right moves it up one level, partly right makes it `shaky`, wrong makes it `weak`.
  3. Run `python3 tracker.py update`.

## Script

```
python3 tracker.py update   # recompute last_practiced and next_review
python3 tracker.py due      # list concepts due for review, weakest first
```
