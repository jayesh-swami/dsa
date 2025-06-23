public class InterleavingStrings {
    boolean[][] memo;
    boolean[][] visited;

    public boolean isInterleave(String s1, String s2, String s3) {

        if (s3.length() != s1.length() + s2.length()) return false;

        memo = new boolean[s1.length() + 1][s2.length() + 1];
        visited = new boolean[s1.length() + 1][s2.length() + 1];

        return isInterleaveUtil(s1, s2, s3, 0, 0, 0);
    }

    private boolean isInterleaveUtil(
            String s1, String s2, String s3, int i, int j, int k) {
        if (k == s3.length()) return i == s1.length() && j == s2.length();

        if (visited[i][j]) return memo[i][j];

        visited[i][j] = true;

        if (i < s1.length() && s1.charAt(i) == s3.charAt(k))
            memo[i][j] = isInterleaveUtil(s1, s2, s3, i + 1, j, k + 1);


        if (!memo[i][j] && j < s2.length() && s2.charAt(j) == s3.charAt(k))
            memo[i][j] = isInterleaveUtil(s1, s2, s3, i, j + 1, k + 1);

        return memo[i][j];
    }
}
