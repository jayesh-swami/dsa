#include <iostream>
#include <vector>

using std::cout;
using std::vector;


/**
 * Bases on the fact that the formula for the sum of rectangle from top left
 * would be a mathematical function of four rectangular regions from top left
 *
 * So we initially compute the sum of all reactangles within a particular region 
 * from top left and then we can query in O(1) time.
 *
 * The initialization cost would be O(n*m) as we can construct this sum matrix 
 * in one pass
 * 
 * One improvement (small) would be to use a padded sumMatrix with first row 
 * and column as zero which would remove the branch and the need for sumFromTopLeft
 * function.
 */
class NumMatrix {
private:
	vector<vector<int>> sumMatrix;

	int sumFromTopLeft(int r, int c) {
		if(r < 0 || c < 0) return 0;

		return sumMatrix[r][c];
	}
public:
	NumMatrix(vector<vector<int>>& matrix) {
		int n = matrix.size();
		int m = matrix[0].size();

		sumMatrix.assign(n, vector<int>(m, 0));

        	for(int i = 0; i < matrix.size(); i++) {
			for(int j = 0; j < matrix[i].size(); j++) {
				sumMatrix[i][j] = 
					sumFromTopLeft(i-1, j) + 
					sumFromTopLeft(i, j-1) - 
					sumFromTopLeft(i-1, j-1) + 
					matrix[i][j];
			}
		}
    	}
	// Assuming correct row and col inputs
	int sumRegion(int row1, int col1, int row2, int col2) {
        	return 	sumFromTopLeft(row2, col2) - 
			sumFromTopLeft(row1 - 1, col2) - 
			sumFromTopLeft(row2, col1 - 1) + 
			sumFromTopLeft(row1 - 1, col1 - 1);
	}
};

/**
 * The optimized version with padded sum matrix
 */
class NumMatrixOptimized {
private:
	vector<vector<int>> sumMatrix;
public:
	NumMatrixOptimized(vector<vector<int>>& matrix) {
		int n = matrix.size();
		int m = matrix[0].size();

		sumMatrix = vector<vector<int>>(n + 1, vector<int>(m + 1, 0));

        	for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				sumMatrix[i+1][j+1] = sumMatrix[i][j+1] + sumMatrix[i+1][j] - sumMatrix[i][j] + matrix[i][j];
			}
		}
    	}
	// Assuming correct row and col inputs
	int sumRegion(int r1, int c1, int r2, int c2) {
		return sumMatrix[r2 + 1][c2 + 1] - sumMatrix[r1][c2 + 1] - sumMatrix[r2 + 1][c1] + sumMatrix[r1][c1];
	}
};

int main() {
	vector<vector<int>> matrix = {
		{3, 0, 1, 4, 2},
		{5, 6, 3, 2, 1},
		{1, 2, 0, 1, 5},
		{4, 1, 0, 1, 7},
		{1, 0, 3, 0, 5}
	};

	NumMatrix nm(matrix);
	NumMatrixOptimized nmo(matrix);

	// Expected: 8 11 12
	cout << nm.sumRegion(2, 1, 4, 3) << " " << nm.sumRegion(1, 1, 2, 2) << " " << nm.sumRegion(1, 2, 2, 4) << "\n";
	cout << nmo.sumRegion(2, 1, 4, 3) << " " << nmo.sumRegion(1, 1, 2, 2) << " " << nmo.sumRegion(1, 2, 2, 4) << "\n";

	return 0;
}
