public class ContainerWithMostWater {

    public int maxArea(int[] heights) {
        int res = 0;

        int i=0, j=heights.length - 1;

        while(i < j && i < heights.length) {
            int areaBetween = (j-i) * Math.min(heights[i], heights[j]);

            if(heights[i] < heights[j]) {
                i++;
            } else if (heights[j] < heights[i]) {
                j--;
            } else {
                i++; j--;
            }

            res = Math.max(areaBetween, res);
        }

        return res;
    }
}
