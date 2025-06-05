public class RottenApples {

    public int orangesRotting(int[][] grid) {
        int[][] oranges = new int[grid.length][grid[0].length];

        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                if (grid[i][j] == 0) {
                    oranges[i][j] = -1;
                } else if (grid[i][j] == 1) {
                    oranges[i][j] = Integer.MAX_VALUE;
                } else {
                    oranges[i][j] = 0;
                }
            }
        }

        for (int i = 0; i < oranges.length; i++) {
            for (int j = 0; j < oranges[i].length; j++) {
                if (oranges[i][j] == 0) {
                    fillOranges(oranges, i, j, 0);
                }
            }
        }

        int maxTime = 0;

        for (int i = 0; i < oranges.length; i++) {
            for (int j = 0; j < oranges[i].length; j++) {
                maxTime = Math.max(maxTime, oranges[i][j]);
            }
        }

        return maxTime == Integer.MAX_VALUE ? -1 : maxTime;
    }

    private void fillOranges(int[][] oranges, int i, int j, int time) {
        if (i < 0 || j < 0 ||
                i >= oranges.length || j >= oranges[i].length ||
                oranges[i][j] == -1 || oranges[i][j] < time) return;

        oranges[i][j] = time;

        fillOranges(oranges, i + 1, j, 1 + time);
        fillOranges(oranges, i - 1, j, 1 + time);
        fillOranges(oranges, i, j - 1, 1 + time);
        fillOranges(oranges, i, j + 1, 1 + time);
    }
}
