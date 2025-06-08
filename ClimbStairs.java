public class ClimbStairs {
    public int climbStairs(int n) {
        int[] memo = new int[n];

        return climbUtil(n, memo);
    }

    private int climbUtil(int n, int[] memo) {
        if (n == 1) return 1;
        if (n == 2) return 2;

        if (memo[n - 1] != 0) return memo[n - 1];

        memo[n - 1] = climbStairs(n - 2) + climbStairs(n - 1);

        return memo[n - 1];
    }
}
