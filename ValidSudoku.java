public class ValidSudoku {

    public boolean isValidSudoku(char[][] board) {
        for (int i = 0; i < 9; i++) {
            if (!checkRow(i, board)) return false;
            if (!checkCol(i, board)) return false;
            if (!checkBox(i / 3, i % 3, board)) return false;
        }
        return true;
    }

    private boolean checkRow(int index, char[][] board) {
        int[] check = new int[9];

        for (int i = 0; i < 9; i++) {
            if (board[i][index] == '.') continue;

            check[board[i][index] - '1']++;
        }

        for (int num : check) {
            if (num > 1) return false;
        }
        return true;
    }

    private boolean checkCol(int index, char[][] board) {
        int[] check = new int[9];

        for (int i = 0; i < 9; i++) {
            if (board[index][i] == '.') continue;

            check[board[index][i] - '1']++;
        }

        for (int num : check) {
            if (num > 1) return false;
        }
        return true;
    }

    private boolean checkBox(int indexRow, int indexCol, char[][] board) {
        int[] check = new int[9];

        for (int i = 3 * indexRow; i < 3 * (indexRow + 1); i++) {
            for (int j = 3 * indexCol; j < 3 * (indexCol + 1); j++) {
                if (board[i][j] == '.') continue;

                check[board[i][j] - '1']++;
            }
        }

        for (int num : check) {
            if (num > 1) return false;
        }
        return true;
    }
}
