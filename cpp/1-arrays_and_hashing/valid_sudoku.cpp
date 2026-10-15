#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <string>

using std::vector;
using std::unordered_set;
using std::sqrt;
using std::cout;
using std::string;

/**
 * A standard 9x9 sudoku
 */
bool isSudokuValid(vector<vector<char>>& board) {
	unordered_set<char> s;

	for(int i = 0; i < 9; i++) {

		s.clear();
		// Check rows
		for(int j = 0; j < 9; j++) {
			if(board[i][j] == '.') continue;
			if(!s.insert(board[i][j]).second) return false;
		}
		s.clear();

		// Check cols
		for(int j = 0; j < 9; j++) {
			if(board[j][i] == '.') continue;
			if(!s.insert(board[j][i]).second) return false;
		}

		s.clear();

		// Check grids
		for(int j = 0; j < 9; j++) {
			char cell = board[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3];

			if(cell == '.') continue;
			if(!s.insert(cell).second) return false;
		}
	}

	return true;
}

/**
 * A general NxN sudoku validator (N must be a perfect square, -1 = empty)
 */
bool isSudokuValidN(vector<vector<int>>& board) {
	unordered_set<int> s;
	int n = board.size();
	int nsqrt = (int) sqrt((double) n);

	if(nsqrt * nsqrt != n) return false;

	for(int i = 0; i < n; i++) {

		s.clear();
		// Check rows
		for(int j = 0; j < n; j++) {
			if(board[i][j] == -1) continue;
			if(!s.insert(board[i][j]).second) return false;
		}
		s.clear();

		// Check cols
		for(int j = 0; j < n; j++) {
			if(board[j][i] == -1) continue;
			if(!s.insert(board[j][i]).second) return false;
		}

		s.clear();

		// Check grids
		for(int j = 0; j < n; j++) {
			int cell = board[(i / nsqrt) * nsqrt + j / nsqrt][(i % nsqrt) * nsqrt + j % nsqrt];

			if(cell == -1) continue;
			if(!s.insert(cell).second) return false;
		}
	}

	return true;
}

// ---- minimal test harness ----

int failures = 0;

void check(const string& name, bool got, bool expected) {
	if (got == expected) {
		cout << "PASS  " << name << '\n';
	} else {
		cout << "FAIL  " << name << "  (expected " << (expected ? "true" : "false")
		     << ", got " << (got ? "true" : "false") << ")\n";
		failures++;
	}
}

vector<vector<char>> toBoard(const vector<string>& rows) {
	vector<vector<char>> board;
	for (const string& r : rows) board.emplace_back(r.begin(), r.end());
	return board;
}

void runTests() {
	// LeetCode 36 example 1
	vector<string> valid = {
		"53..7....",
		"6..195...",
		".98....6.",
		"8...6...3",
		"4..8.3..1",
		"7...2...6",
		".6....28.",
		"...419..5",
		"....8..79",
	};

	auto b = toBoard(valid);
	check("9x9 valid partial board", isSudokuValid(b), true);

	b = toBoard(vector<string>(9, "........."));
	check("9x9 empty board", isSudokuValid(b), true);

	b = toBoard({
		"534678912",
		"672195348",
		"198342567",
		"859761423",
		"426853791",
		"713924856",
		"961537284",
		"287419635",
		"345286179",
	});
	check("9x9 fully solved board", isSudokuValid(b), true);

	// LeetCode 36 example 2: duplicate 8 in top-left box and first column
	b = toBoard(valid);
	b[0][0] = '8';
	check("9x9 dup in column + box", isSudokuValid(b), false);

	b = toBoard(valid);
	b[0][8] = '7';
	check("9x9 dup in row only", isSudokuValid(b), false);

	b = toBoard(valid);
	b[8][0] = '5';
	check("9x9 dup in column only", isSudokuValid(b), false);

	// (1,1) and (0,0) share the top-left box but no row/column
	b = toBoard(vector<string>(9, "........."));
	b[0][0] = '1';
	b[1][1] = '1';
	check("9x9 dup in box only", isSudokuValid(b), false);

	// dup in the last (bottom-right) box exercises the box index math
	b = toBoard(vector<string>(9, "........."));
	b[6][6] = '9';
	b[8][8] = '9';
	check("9x9 dup in bottom-right box", isSudokuValid(b), false);

	// ---- NxN ----

	vector<vector<int>> n4 = {
		{1, 2, 3, 4},
		{3, 4, 1, 2},
		{2, 1, 4, 3},
		{4, 3, 2, 1},
	};
	check("4x4 solved board", isSudokuValidN(n4), true);

	vector<vector<int>> n4p = {
		{ 1, -1, -1, -1},
		{-1, -1,  1, -1},
		{-1,  1, -1, -1},
		{-1, -1, -1,  1},
	};
	check("4x4 partial board", isSudokuValidN(n4p), true);

	n4p[0][1] = 1;
	check("4x4 dup in row", isSudokuValidN(n4p), false);

	vector<vector<int>> n4box(4, vector<int>(4, -1));
	n4box[2][2] = 3;
	n4box[3][3] = 3;
	check("4x4 dup in box only", isSudokuValidN(n4box), false);

	vector<vector<int>> n1 = {{1}};
	check("1x1 board", isSudokuValidN(n1), true);

	vector<vector<int>> n3(3, vector<int>(3, -1));
	check("3x3 not a perfect square", isSudokuValidN(n3), false);

	// 9x9 via the generic version should agree with the char version
	vector<vector<int>> n9(9, vector<int>(9, -1));
	auto cb = toBoard(valid);
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (cb[i][j] != '.') n9[i][j] = cb[i][j] - '0';
	check("9x9 via NxN valid", isSudokuValidN(n9), true);
	n9[0][0] = 8;
	check("9x9 via NxN dup", isSudokuValidN(n9), false);
}

int main() {
	runTests();

	cout << '\n' << (failures == 0 ? "All tests passed" : "Some tests failed") << '\n';
	return failures == 0 ? 0 : 1;
}
