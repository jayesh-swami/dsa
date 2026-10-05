import java.util.LinkedList;
import java.util.Queue;

public class NumIslandsBfs {
    private boolean[][] visited;

    public int numIslands(char[][] grid) {

        int numIslands = 0;
        visited = new boolean[grid.length][grid[0].length];

        for(int i = 0 ; i < grid.length ; i++) {
            for(int j = 0 ; j < grid[i].length ; j++) {
                if(!visited[i][j] && grid[i][j] == '1') {
                    numIslands++;
                    bfs(grid, i, j);
                }
            }
        }

        return numIslands;

    }

    private void bfs(char[][] grid, int i, int j) {

        Queue<int[]> queue = new LinkedList<>();

        queue.add(new int[] {i, j});

        while(!queue.isEmpty()) {
            int[] currentCell = queue.poll();
            int row = currentCell[0];
            int col = currentCell[1];

            if(row < 0 ||
                    col < 0 ||
                    row >= grid.length ||
                    col >= grid[row].length ||
                    visited[row][col] ||
                    grid[row][col] == '0') continue;

            visited[row][col] = true;

            queue.offer(new int[] {row + 1, col});
            queue.offer(new int[] {row - 1, col});
            queue.offer(new int[] {row, col + 1});
            queue.offer(new int[] {row, col - 1});
        }
    }
}
