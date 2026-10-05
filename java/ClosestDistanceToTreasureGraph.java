public class ClosestDistanceToTreasureGraph {
    public void islandsAndTreasure(int[][] grid) {
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                if (grid[i][j] == 0) fillPath(grid, i, j, 0);
            }
        }
    }

    private void fillPath(int[][] grid, int i, int j, int distance) {
        if (i < 0 || j < 0 ||
                i >= grid.length || j >= grid[i].length ||
                grid[i][j] == -1 || grid[i][j] < distance) return;

        grid[i][j] = distance;

        fillPath(grid, i + 1, j, 1 + distance);
        fillPath(grid, i - 1, j, 1 + distance);
        fillPath(grid, i, j - 1, 1 + distance);
        fillPath(grid, i, j + 1, 1 + distance);
    }
}
