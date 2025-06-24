public class BInarySearchSplitSquares {

    public double separateSquares(int[][] squares) {
        double low = Double.MAX_VALUE, high = Double.MIN_VALUE;

        for (int i = 0; i < squares.length; i++) {
            low = Math.min(low, Double.valueOf(squares[i][1]));
            high = Math.max(high, Double.valueOf(squares[i][1] + squares[i][2]));
        }

        while (high - low > 1e-5) {
            double mid = (high + low) / 2.0d;
            double areaDiff = squareAreaDiff(squares, mid);

            if (areaDiff > 0) {
                low = mid;
            } else {
                high = mid;
            }
        }

        return (high + low) / 2;

    }

    private double squareAreaDiff(int[][] squares, double y) {
        double top = 0.0d;
        double bottom = 0.0d;

        for (int i = 0; i < squares.length; i++) {
            double side = squares[i][2];
            double topEdge = squares[i][1] + squares[i][2];
            double bottomEdge = squares[i][1];

            if (y < topEdge && y > bottomEdge) {
                top += side * (topEdge - y);
                bottom += side * (y - bottomEdge);
            }

            if (y <= bottomEdge) top += side * side;

            if (y >= topEdge) bottom += side * side;
        }

        return top - bottom;
    }
}
