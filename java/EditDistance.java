public class EditDistance {
    int memo[][];

    public int minDistance(String word1, String word2) {
        memo = new int[word1.length()][word2.length()];

        return editDistance(word1, word2, 0, 0);
    }

    private int editDistance(String s1, String s2, int i, int j) {
        if (i == s1.length() && j == s2.length()) return 0;

        if (i == s1.length()) return s2.length() - j;

        if (j == s2.length()) return s1.length() - i;

        if (memo[i][j] != 0) return memo[i][j];

        if (s1.charAt(i) == s2.charAt(j)) {
            memo[i][j] = editDistance(s1, s2, i + 1, j + 1);
        } else {
            memo[i][j] = Math.min(
                    Math.min(
                            editDistance(s1, s2, i + 1, j) + 1,
                            editDistance(s1, s2, i, j + 1) + 1
                    ),
                    editDistance(s1, s2, i + 1, j + 1) + 1
            );
        }

        return memo[i][j];
    }
}
