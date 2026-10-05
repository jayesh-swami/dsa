public class LongestPalindrome {

    public String longestPalindrome(String s) {
        String result = "";

        for (int i = 0; i < s.length(); i++) {
            String odd = longestOddPalindrome(i, s);
            String even = longestEvenPalindrome(i, i + 1, s);

            if (odd.length() > result.length()) {
                result = odd;
            }

            if (even.length() > result.length()) {
                result = even;
            }
        }

        return result;
    }

    private String longestOddPalindrome(int center, String s) {
        int left = center;
        int right = center;

        String res = "";

        while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
            left--;
            right++;
        }

        return s.substring(left + 1, right);
    }

    private String longestEvenPalindrome(int leftCenter, int rightCenter, String s) {
        int left = leftCenter;
        int right = rightCenter;

        String res = "";

        while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
            left--;
            right++;
        }

        return s.substring(left + 1, right);
    }
}
