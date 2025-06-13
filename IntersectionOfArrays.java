import java.util.*;

public class IntersectionOfArrays {
    public int[] intersection(int[] nums1, int[] nums2) {
        Set<Integer> set = new HashSet<>();
        Set<Integer> res = new HashSet<>();

        for (int num : nums1) set.add(num);

        for (int num : nums2) if (set.contains(num)) res.add(num);

        int[] result = new int[res.size()];

        int i = 0;

        for (int val : res) {
            result[i] = val;
            i++;
        }

        return result;
    }
}
