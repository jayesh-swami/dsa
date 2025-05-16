public class NonDecreasingArray {

    /**
     * If there are more violations than 1, then we need more than 1 change hence false
     *
     * If there is only one violation then we check that one of the following is true -
     *      1.  Either violation element pair is at beginning or end of the array (i == 0 || i == len-2)
     *      2.  Either the first or the second element in the violation pair can be changed - For this we check
     *          the i-1 and i+1 pair OR i and i+2 pair are in non-decreasing order or not.
     */

    public boolean checkPossibility(int[] nums) {
        int violations = 0;

        for (int i = 0; i < nums.length - 1; i++) {
            if (nums[i] > nums[i + 1]) {
                violations++;
                if (violations > 1) return false;
                if (!(
                        i == 0
                        || nums[i - 1] <= nums[i + 1]
                        || i == nums.length - 2
                        || nums[i + 2] >= nums[i])) return false;
            }
        }
        return true;
    }

}
