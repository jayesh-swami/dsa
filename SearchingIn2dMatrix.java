public class SearchingIn2dMatrix {

    public boolean searchMatrix(int[][] matrix, int target) {
        int row = -1;

        int low = 0, high = matrix.length - 1;

        while (low <= high) {
            int mid = (high + low) / 2;

            if (matrix[mid][0] == target) {
                return true;
            } else if (matrix[mid][0] < target) {
                row = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        if (row == -1) return false;

        low = 0;
        high = matrix[row].length - 1;

        while (low <= high) {
            int mid = (high + low) / 2;

            if (matrix[row][mid] == target) {
                return true;
            } else if (matrix[row][mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return false;
    }

}
