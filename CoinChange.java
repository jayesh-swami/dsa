import java.util.HashMap;

public class CoinChange {
    HashMap<Integer, Integer> memo = new HashMap<>();

    public int coinChange(int[] coins, int amount) {
        int res = coinChangeUtil(coins, amount);

        return res == Integer.MAX_VALUE ? -1 : res;
    }

    private int coinChangeUtil(int[] coins, int amount) {
        if (amount == 0) return 0;
        if (memo.containsKey(amount))
            return memo.get(amount);

        int res = Integer.MAX_VALUE;

        for (int coin : coins) {

            if (amount - coin >= 0) {
                int minCoins = coinChangeUtil(coins, amount - coin);

                if (minCoins != Integer.MAX_VALUE) {
                    res = Math.min(res, 1 + minCoins);
                }
            }
        }

        memo.put(amount, res);
        return res;
    }
}
