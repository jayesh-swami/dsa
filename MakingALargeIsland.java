import java.util.*;

public class MakingALargeIsland {
    public int largestIsland(int[][] grid) {
        if (grid.length <= 0) return 0;

        boolean[][] visited = new boolean[grid.length][grid[0].length];
        Map<Integer, Integer> islandSizeMap = new HashMap<>();
        islandSizeMap.put(0, 0);

        int islandCount = 2;
        int res = 0;

        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                if (!visited[i][j]) {
                    int sizeOfIsland = dfs(grid, i, j, visited, islandCount);
                    islandSizeMap.put(islandCount, sizeOfIsland);
                    res = Math.max(res, sizeOfIsland);
                    islandCount++;
                }
            }
        }

        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                if (grid[i][j] == 0) {
                    res = Math.max(res, connectIslands(grid, i, j, islandSizeMap));
                }
            }
        }

        return res;
    }

    private int connectIslands(int[][] grid, int i, int j, Map<Integer, Integer> islandSizeMap) {
        Set<Integer> nearbyIslandIds = new HashSet<>();

        nearbyIslandIds.add(i == 0 ? 0 : grid[i - 1][j]);
        nearbyIslandIds.add(i == grid.length - 1 ? 0 : grid[i + 1][j]);
        nearbyIslandIds.add(j == 0 ? 0 : grid[i][j - 1]);
        nearbyIslandIds.add(j == grid[i].length - 1 ? 0 : grid[i][j + 1]);

        int res = 1;

        for (Integer islandId : nearbyIslandIds) res += islandSizeMap.get(islandId);

        return res;
    }

    private int dfs(int[][] grid, int i, int j, boolean[][] visited, int islandId) {
        if (i < 0 ||
                j < 0 ||
                i >= grid.length ||
                j >= grid[i].length ||
                grid[i][j] == 0 ||
                visited[i][j]) return 0;

        visited[i][j] = true;
        grid[i][j] = islandId;

        return dfs(grid, i + 1, j, visited, islandId) +
                dfs(grid, i - 1, j, visited, islandId) +
                dfs(grid, i, j + 1, visited, islandId) +
                dfs(grid, i, j - 1, visited, islandId) + 1;
    }
}
