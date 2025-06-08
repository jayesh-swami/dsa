public class DecodeWays {

    public int numDecodings(String s) {
        int[] memo = new int[s.length()];

        for (int i = 0; i < memo.length; i++) {
            memo[i] = -1;
        }

        return numDecodingsUtil(s, 0, memo);
    }

    private int numDecodingsUtil(String s, int currentChar, int[] memo) {
        if (currentChar == s.length()) return 1;
        if (s.charAt(currentChar) == '0') return 0;

        if (memo[currentChar] != -1) return memo[currentChar];

        memo[currentChar] = numDecodingsUtil(s, currentChar + 1, memo);

        if (canDecodeTwo(s, currentChar)) {
            memo[currentChar] += numDecodingsUtil(s, currentChar + 2, memo);
        }

        return memo[currentChar];
    }

    private boolean canDecodeTwo(String s, int start) {
        if (start == s.length() - 1) return false;
        return s.charAt(start) == '1' ||
                (s.charAt(start) == '2' && s.charAt(start + 1) < '7');
    }
}
