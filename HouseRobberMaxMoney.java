public class HouseRobberMaxMoney {
    public int rob(int[] nums) {
        int[] memo = new int[nums.length];

        for (int i = 0; i < memo.length; i++) {
            memo[i] = -1;
        }

        return robUtil(nums.length - 1, nums, memo);
    }

    private int robUtil(int currentHouse, int[] money, int[] memo) {
        if (currentHouse < 0) return 0;
        if (currentHouse == 0) return money[0];
        if (memo[currentHouse] != -1) return memo[currentHouse];

        memo[currentHouse] = Math.max(
                money[currentHouse] + robUtil(currentHouse - 2, money, memo),
                robUtil(currentHouse - 1, money, memo));

        return memo[currentHouse];
    }
}
