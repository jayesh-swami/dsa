public class MinCostClimbing {
    public int minCostClimbingStairs(int[] cost) {
        int[] memo = new int[cost.length + 1];

        for (int i = 0; i < memo.length; i++) {
            memo[i] = -1;
        }

        return minCostClimbUtil(cost.length, cost, memo);
    }

    private int minCostClimbUtil(int currentStep, int[] cost, int[] memo) {
        if (currentStep == 0 || currentStep == 1) return 0;
        if (memo[currentStep] != -1) return memo[currentStep];

        memo[currentStep] = Math.min(
                cost[currentStep - 1] + minCostClimbUtil(currentStep - 1, cost, memo),
                cost[currentStep - 2] + minCostClimbUtil(currentStep - 2, cost, memo));

        return memo[currentStep];
    }
}
