import java.util.Arrays;

public class LongestIncreasingPathInAMatrix {
    int memo[][];

    public int longestIncreasingPath(int[][] matrix) {
        memo = new int[matrix.length][matrix[0].length];

        for (int i = 0; i < matrix.length; i++) Arrays.fill(memo[i], -1);

        int res = -1;

        for (int i = 0; i < memo.length; i++) {
            for (int j = 0; j < memo[i].length; j++) {
                if (memo[i][j] == -1) lip(matrix, i, j, Integer.MIN_VALUE);
                res = Math.max(res, memo[i][j]);
            }
        }

        return res;
    }

    private int lip(int[][] matrix, int i, int j, int parent) {
        if (i < 0 ||
                j < 0 ||
                i >= matrix.length ||
                j >= matrix[i].length ||
                matrix[i][j] <= parent)
            return 0;

        if (memo[i][j] != -1) return memo[i][j];


        memo[i][j] = Math.max(
                Math.max(lip(matrix, i + 1, j, matrix[i][j]), lip(matrix, i - 1, j, matrix[i][j])),
                Math.max(lip(matrix, i, j + 1, matrix[i][j]), lip(matrix, i, j - 1, matrix[i][j]))
        ) + 1;

        return memo[i][j];
    }
}
