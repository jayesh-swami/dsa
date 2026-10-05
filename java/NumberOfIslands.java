public class NumberOfIslands {
    private int islands = 0;

    public int numIslands(char[][] grid) {
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                if (grid[i][j] == '1') {
                    islands++;
                    fillIsland(grid, i, j);
                }
            }
        }
        return islands;
    }

    private void fillIsland(char[][] grid, int i, int j) {
        if (i < 0 || i >= grid.length || j < 0 || j >= grid[i].length || grid[i][j] == '0') return;

        grid[i][j] = '0';

        fillIsland(grid, i + 1, j);
        fillIsland(grid, i - 1, j);
        fillIsland(grid, i, j + 1);
        fillIsland(grid, i, j - 1);
    }
}
