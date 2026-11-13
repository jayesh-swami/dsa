# Contests — Notes

Concepts that came up in contests. Solutions are in `codeforces/<contest id>-round_<n>_<div>/`.

# Concepts

## Fast I/O: buffers, flushing and the OS

**The OS does the actual I/O.** A program can't touch the screen, files or other programs itself. It asks the kernel with a **system call**:

```
write(1, ptr, n)   // send n bytes to output channel 1
read(0, ptr, n)    // get up to n bytes from input channel 0
```

- 0, 1, 2 are **file descriptors**: stdin, stdout, stderr. On a judge, fd 0 is the test input and fd 1 goes to a file the checker reads.
- A syscall is expensive: switch into kernel mode, checks, switch back. That costs hundreds of ns or more, against about 1 ns to copy a byte in your own memory.

**A buffer batches the syscalls.** The I/O library keeps an array of a few KB inside your process. `cout << x` only formats into that array, which is cheap. One `write` then sends thousands of prints at once. Input works the same way: one `read` pulls in a chunk, and `cin >> x` parses from memory.

- **Flush** = hand what's in the buffer to the kernel now. It happens when the buffer is full, on `endl` / `cout.flush()`, on a normal exit, and before each `cin` read while `cin` is tied to `cout`.
- Until it's flushed, the output exists **only inside your process**.

**`ios::sync_with_stdio(false)`.** C++ has two I/O libraries writing to the same fd 1: C stdio (`printf`, `scanf`) and iostreams (`cout`, `cin`).
- With two independent buffers, `printf("A"); cout << "B"; printf("C");` could print `ACB`.
- So by default iostreams are **synchronised** with stdio: `cout` has no buffer of its own and passes every character through to C's stdio. That's safe but slow.
- `sync_with_stdio(false)` gives `cin`/`cout` their own buffers, which is fast. **After it, don't mix `printf`/`scanf` with `cin`/`cout`**, or the output order can break.

**`cin.tie(nullptr)`.** By default `cin` is tied to `cout`, so `cout` is flushed before every `cin >>`. That exists so a console prompt (`cout << "Name: "; cin >> name;`) shows up before the program waits.
- In a contest that read/print alternation can mean 2·10⁵ flushes, i.e. 2·10⁵ syscalls. Untying removes them. The judge only reads the output at the end anyway.

**Interactive problems.** The judge is another program running at the same time, connected to your stdin and stdout by pipes.
- If a query sits in your buffer, the judge never receives it. It waits for you, and you wait in `cin` for it, so you get *Idleness limit exceeded*.
- **Flush after every query:** `cout << "? " << x << endl;` (`endl` = `'\n'` + flush). With the tie removed, nothing flushes for you.

**Practical rules:**
- In normal problems, use `'\n'`, not `endl`. `endl` flushes every line, so 10⁵ lines means 10⁵ syscalls, which can be a TLE on its own.
- Buffers are flushed only on a **normal** exit. After a segfault, whatever was still in the buffer is lost, so debug prints seem to stop earlier than the crash. Print debug output to `cerr`, which is unbuffered. Judges ignore stderr.
- The contest header is just these two lines:
  ```cpp
  ios::sync_with_stdio(false);  // own fast buffers: no printf/scanf after this
  cin.tie(nullptr);             // no flush before each read: flush yourself in interactive problems
  ```
- Why it matters beyond contests: cutting down syscalls and controlling when data actually leaves the process is a core low-latency idea. It applies the same way to sockets.

## Binary search on the answer
- "Minimise X subject to a budget" has two things changing at once. Turn it into a yes/no question: **"can X ≤ D within the budget?"** If D works, every larger D works too (monotone), so binary search for the smallest D that works.
- The check is usually easier than the original problem: with D fixed, compute the **least** cost for D and compare it with the budget.
- Bounds: `lo` = the smallest D that could ever work (often 0, which may itself be the answer). `hi` = a value known to work for free (e.g. the current value with no changes).
- Use one template throughout, e.g. `while (lo <= hi)` with a saved answer: on success save `mid` and set `hi = mid - 1`, otherwise `lo = mid + 1`.
- Signal for it: huge budgets (k ≤ 10¹⁸) rule out simulating one unit at a time, and the answer range is large but the check is cheap. Total: O(check · log(range)).
- Seen in: CF2290G Lakeside Trail.

## Limit the slope by raising only (two passes)
- Heights can only go up, and every adjacent difference must be ≤ D. Each point must end at least `h_j − D·dist(i, j)` for every `j`: a **tent** with slope D under every peak. The cheapest result is the top of all the tents: `g_i = max over j of (h_j − D·dist(i, j))`. That's both a lower bound and valid, so it's optimal.
- O(n) instead of O(n²): carry a demand that drops by D each step and resets upward at taller points, `cur = max(h_i, cur − D)`. Do one pass each way and take the max of the two values at each point.
- **On a circle:** start both passes at the global max (it never needs raising) and let **each pass go all the way round**. Stopping when the two pointers meet is wrong, because a point only sees the peaks on one side. Counterexample: `h = [10, 1, 1, 1, 9, 1, 1]`, `D = 3`. Index 3 needs 6 (from the 9), but the meet-in-the-middle version gives 1.
- Running the second pass on the heights already raised by the first counts only the extra soil, so the summed cost is exactly Σ (g_i − h_i).
- Seen in: CF2290G Lakeside Trail.
