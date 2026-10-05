public class LongestIncreasingSubsequence {
    public int lengthOfLIS(int[] nums) {

        int[] memo = new int[nums.length];

        int res = 1;

        for (int i = 0; i < nums.length; i++) {
            res = Math.max(res, lisUtil(nums, i, memo));
        }
        return res;
    }

    private int lisUtil(int[] nums, int index, int[] memo) {
        if (index == 0) return 1;
        if (memo[index] != 0) return memo[index];

        int res = 1;

        for (int i = 0; i < index; i++) {
            if (nums[index] > nums[i]) {
                res = Math.max(res, lisUtil(nums, i, memo) + 1);
            }
        }
        memo[index] = res;
        return res;
    }
}
