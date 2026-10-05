import java.util.*;

public class FourSum {
    Map<Integer, Integer> sumOfFirstTwo = new HashMap<>();

    public int fourSumCount(int[] nums1, int[] nums2, int[] nums3, int[] nums4) {

        for (int i = 0; i < nums1.length; i++) {
            for (int j = 0; j < nums2.length; j++) {
                sumOfFirstTwo.put(nums1[i] + nums2[j], sumOfFirstTwo.getOrDefault(nums1[i] + nums2[j], 0) + 1);
            }
        }

        int res = 0;

        for (int i = 0; i < nums3.length; i++) {
            for (int j = 0; j < nums4.length; j++) {
                int sum = nums3[i] + nums4[j];

                res += sumOfFirstTwo.getOrDefault(sum * -1, 0);
            }
        }

        return res;
    }
}
