public class SurroundedRegions {
    public void solve(char[][] board) {
        for (int i = 0; i < board.length; i++) {
            if (board[i][0] == 'O') fill(board, i, 0);
            if (board[i][board[0].length - 1] == 'O') fill(board, i, board[0].length - 1);
        }

        for (int i = 1; i < board[0].length - 1; i++) {
            if (board[0][i] == 'O') fill(board, 0, i);
            if (board[board.length - 1][i] == 'O') fill(board, board.length - 1, i);
        }

        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                if (board[i][j] == 'A') board[i][j] = 'O';
            }
        }
    }

    private void fill(char[][] board, int i, int j) {
        if (i < 0 || j < 0 ||
                i >= board.length || j >= board[i].length ||
                board[i][j] == 'X' || board[i][j] == 'A') return;

        board[i][j] = 'A';

        fill(board, i + 1, j);
        fill(board, i - 1, j);
        fill(board, i, j + 1);
        fill(board, i, j - 1);
    }
}
