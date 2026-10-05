public class UniquePaths {

    public int uniquePaths(int m, int n) {
        int[][] memo = new int[m][n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                memo[i][j] = -1;
            }
        }

        return uniquePathsUtil(m - 1, n - 1, memo);
    }

    private int uniquePathsUtil(int m, int n, int[][] memo) {
        if (m == 0 && n == 0) return 1;

        if (m == 0) return 1;
        if (n == 0) return 1;

        if (memo[m][n] != -1) return memo[m][n];

        memo[m][n] = uniquePathsUtil(m - 1, n, memo) + uniquePathsUtil(m, n - 1, memo);
        return memo[m][n];
    }
}
