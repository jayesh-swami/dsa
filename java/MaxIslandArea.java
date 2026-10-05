public class MaxIslandArea {

    public int maxAreaOfIsland(int[][] grid) {
        int maxArea = 0;

        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                if (grid[i][j] == 1) {
                    maxArea = Math.max(maxArea, islandArea(grid, i, j));
                }
            }
        }

        return maxArea;
    }

    private int islandArea(int[][] grid, int i, int j) {
        if (i < 0 || i >= grid.length || j < 0
                || j >= grid[i].length || grid[i][j] == 0) return 0;

        grid[i][j] = 0;

        int left = islandArea(grid, i - 1, j);
        int right = islandArea(grid, i + 1, j);
        int top = islandArea(grid, i, j - 1);
        int bottom = islandArea(grid, i, j + 1);

        return 1 + left + right + top + bottom;
    }
}
