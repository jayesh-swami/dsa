import java.util.Arrays;

public class TargetSum {
    int memo[][];
    int maxPossibleSum = 0;

    public int findTargetSumWays(int[] nums, int target) {
        for (int i = 0; i < nums.length; i++) maxPossibleSum += nums[i];

        memo = new int[nums.length][2 * (maxPossibleSum + Math.abs(target)) + 1];

        for (int i = 0; i < nums.length; i++) Arrays.fill(memo[i], -1);

        return findTargetUtil(nums, target, 0, 0);
    }

    private int findTargetUtil(int[] nums, int target, int i, int currentTotal) {
        if (i == nums.length) return currentTotal == target ? 1 : 0;

        if (memo[i][currentTotal + maxPossibleSum] != -1)
            return memo[i][currentTotal + maxPossibleSum];

        memo[i][currentTotal + maxPossibleSum] =
                findTargetUtil(nums, target, i + 1, currentTotal + nums[i]) +
                        findTargetUtil(nums, target, i + 1, currentTotal - nums[i]);

        return memo[i][currentTotal + maxPossibleSum];
    }
}
