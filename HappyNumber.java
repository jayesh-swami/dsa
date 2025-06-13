import java.util.*;

public class HappyNumber {
    public boolean isHappy(int n) {
        Set<Integer> set = new HashSet<>();

        while (true) {
            n = squareOfDigits(n);

            if (n == 1) return true;

            if (set.contains(n)) return false;

            set.add(n);
        }
    }

    private int squareOfDigits(int n) {
        int square = 0;

        while (n != 0) {
            int digit = n % 10;
            square += digit * digit;
            n = n / 10;
        }
        return square;
    }
}
