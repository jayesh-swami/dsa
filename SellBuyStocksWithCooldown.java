import java.util.Arrays;

public class SellBuyStocksWithCooldown {
    int[] memo;

    public int maxProfit(int[] prices) {
        memo = new int[prices.length];

        Arrays.fill(memo, Integer.MIN_VALUE);

        return maxProfitUtil(prices, prices.length - 1);
    }

    private int maxProfitUtil(int[] prices, int idx) {
        if (idx <= 0) return 0;

        if (memo[idx] != Integer.MIN_VALUE) return memo[idx];

        int maxProf = 0;

        for (int i = 0; i < idx; i++) {
            if (prices[i] < prices[idx]) {
                maxProf = Math.max(
                        maxProfitUtil(prices, i - 2) + prices[idx] - prices[i],
                        maxProf);
            }
        }

        maxProf = Math.max(maxProfitUtil(prices, idx - 1), maxProf);

        memo[idx] = maxProf;

        return maxProf;
    }
}
