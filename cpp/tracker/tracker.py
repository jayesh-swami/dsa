"""Keep concepts.csv in sync with problems.csv and quizzes.csv, and show what's due.

    python3 tracker.py update   # recompute last_practiced and next_review
    python3 tracker.py due      # concepts due for review, weakest first
"""
import csv
import sys
from datetime import date, timedelta
from pathlib import Path

DIR = Path(__file__).parent
# Days until the next review, by strength. "untested" is due right away.
INTERVAL = {"weak": 2, "shaky": 5, "solid": 14, "untested": 0}
ORDER = ["weak", "untested", "shaky", "solid"]


def read(name):
    with open(DIR / name, newline="") as f:
        return list(csv.DictReader(f))


def write(name, rows):
    with open(DIR / name, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=rows[0].keys(), lineterminator="\n")
        w.writeheader()
        w.writerows(rows)


def split(s):
    return [x for x in s.split(";") if x]


def update():
    concepts = read("concepts.csv")
    last = {}
    for p in read("problems.csv"):
        for c in split(p["concepts"]):
            last[c] = max(last.get(c, ""), p["date"])
    for q in read("quizzes.csv"):
        for c in split(q["correct"]) + split(q["partial"]) + split(q["wrong"]):
            last[c] = max(last.get(c, ""), q["date"])

    known = {c["id"] for c in concepts}
    unknown = sorted(set(last) - known)
    if unknown:
        sys.exit(f"Unknown concept ids: {', '.join(unknown)}")

    for c in concepts:
        c["last_practiced"] = last.get(c["id"], "")
        days = INTERVAL[c["strength"]]
        start = date.fromisoformat(c["last_practiced"]) if c["last_practiced"] else date.today()
        c["next_review"] = (start + timedelta(days=days)).isoformat()
    write("concepts.csv", concepts)
    print(f"Updated {len(concepts)} concepts.")


def due():
    today = date.today().isoformat()
    rows = [c for c in read("concepts.csv") if c["next_review"] <= today]
    rows.sort(key=lambda c: (ORDER.index(c["strength"]), c["next_review"]))
    for c in rows:
        print(f"{c['strength']:9} {c['next_review']}  {c['id']:28} {c['concept']}")
    print(f"\n{len(rows)} due.")


if __name__ == "__main__":
    {"update": update, "due": due}[sys.argv[1] if len(sys.argv) > 1 else "due"]()
