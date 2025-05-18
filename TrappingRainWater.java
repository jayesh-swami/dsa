/**
 * Two arrays to store prefix max and post max. The amount of water that can be trapped at particular point
 * is min of premax/postmax - curHeight. If currheight is negative then water trapped is zero.
 */
public class TrappingRainWater {
    public int trap(int[] height) {
        int[] pre = new int[height.length];
        int[] post = new int[height.length];

        int res = 0;

        for(int i = 1; i < height.length ; i++) {
            pre[i] = Math.max(pre[i-1], height[i-1]);
        }

        for(int i = height.length - 2; i >= 0 ; i--) {
            post[i] = Math.max(post[i+1], height[i+1]);
        }

        for(int i = 0 ; i < height.length ; i++) {
            res += Math.max(Math.min(pre[i], post[i]) - height[i], 0);
        }

        return res;
    }
}
