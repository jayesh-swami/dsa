public class ProductExceptSelf {

    public int[] productExceptSelf(int[] nums) {
        int[] numsProductLeft = new int[nums.length];
        int[] numsProductRight = new int[nums.length];
        int[] result = new int[nums.length];

        for(int i = 0; i < nums.length ; i++) {
            numsProductLeft[i] = 1;
            numsProductRight[i] = 1;
        }

        for(int i = 1 ; i < nums.length ; i++) {
            numsProductLeft[i] = numsProductLeft[i-1] * nums[i-1];
        }

        for(int i = nums.length - 2 ; i >= 0 ; i--) {
            numsProductRight[i] = numsProductRight[i+1] * nums[i+1];
        }

        for(int i = 0 ; i < nums.length; i++) {
            result[i] = numsProductLeft[i] * numsProductRight[i];
        }

        return result;
    }

}
