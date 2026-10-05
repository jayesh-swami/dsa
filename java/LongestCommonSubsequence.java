import java.util.Arrays;

public class LongestCommonSubsequence {
    int[][] memo;

    public int longestCommonSubsequence(String text1, String text2) {

        memo = new int[text1.length()][text2.length()];

        for (int i = 0; i < text1.length(); i++)
            Arrays.fill(memo[i], Integer.MIN_VALUE);

        return lcs(text1, text2, text1.length() - 1, text2.length() - 1);
    }

    private int lcs(String s1, String s2, int idx1, int idx2) {
        if (idx1 < 0 || idx2 < 0) return 0;

        if (memo[idx1][idx2] != Integer.MIN_VALUE)
            return memo[idx1][idx2];

        if (s1.charAt(idx1) == s2.charAt(idx2)) {
            memo[idx1][idx2] = 1 + lcs(s1, s2, idx1 - 1, idx2 - 1);
        } else {
            memo[idx1][idx2] = Math.max(lcs(s1, s2, idx1, idx2 - 1), lcs(s1, s2, idx1 - 1, idx2));
        }

        return memo[idx1][idx2];
    }
}
