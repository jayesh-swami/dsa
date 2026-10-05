public class KokoEatingBananas {

    public int minEatingSpeed(int[] piles, int h) {
        int minPossibleSpeed = 1;
        int maxPossibleSpeed = -1;

        for (int i = 0; i < piles.length; i++) {
            maxPossibleSpeed = Math.max(maxPossibleSpeed, piles[i]);
        }

        int low = minPossibleSpeed, high = maxPossibleSpeed;

        int res = maxPossibleSpeed;
        while (low <= high) {
            int mid = (low + high) / 2;

            if (canEatBananas(piles, h, mid)) {
                high = mid - 1;
                res = mid;
            } else {
                low = mid + 1;
            }
        }

        return res;
    }

    private boolean canEatBananas(int[] piles, int hours, int speed) {
        for (int i = 0; i < piles.length; i++) {
            if (piles[i] % speed == 0) {
                hours -= piles[i] / speed;
            } else {
                hours -= (piles[i] / speed) + 1;
            }
        }

        return hours >= 0;
    }

}
