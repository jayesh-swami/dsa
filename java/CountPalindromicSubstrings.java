public class CountPalindromicSubstrings {

    public int countSubstrings(String s) {
        int res = 0;

        for (int i = 0; i < s.length(); i++) {
            res += countOddPalindrome(i, s) + countEvenPalindrome(i, i + 1, s);
        }

        return res;
    }

    private int countOddPalindrome(int center, String s) {
        int left = center;
        int right = center;

        int res = 0;

        while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
            left--;
            right++;
            res++;
        }

        return res;
    }

    private int countEvenPalindrome(int leftCenter, int rightCenter, String s) {
        int left = leftCenter;
        int right = rightCenter;

        int res = 0;

        while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
            left--;
            right++;
            res++;
        }

        return res;
    }
}
