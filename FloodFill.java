public class FloodFill {
    public int[][] floodFill(int[][] image, int sr, int sc, int color) {
        floodFillUtil(image, sr, sc, color, image[sr][sc]);

        return image;
    }

    private void floodFillUtil(int[][] image, int sr, int sc, int color, int originalColor) {
        if(sr < 0 ||
                sc < 0 ||
                sr >= image.length ||
                sc >= image[sr].length ||
                image[sr][sc] != originalColor ||
                image[sr][sc] == color) return;

        image[sr][sc] = color;

        floodFillUtil(image, sr + 1, sc, color, originalColor);
        floodFillUtil(image, sr - 1, sc, color, originalColor);
        floodFillUtil(image, sr, sc + 1, color, originalColor);
        floodFillUtil(image, sr, sc - 1, color, originalColor);
    }
}
