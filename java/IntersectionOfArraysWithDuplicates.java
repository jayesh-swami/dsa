import java.util.*;

public class IntersectionOfArraysWithDuplicates {
    public int[] intersect(int[] nums1, int[] nums2) {

        Map<Integer, Integer> mp1 = new HashMap<>();

        for (int num : nums1) mp1.put(num, mp1.getOrDefault(num, 0) + 1);

        Map<Integer, Integer> mp2 = new HashMap<>();

        int size = 0;

        for (int num : nums2) {
            if (mp1.containsKey(num) && mp1.get(num) > 0) {
                mp2.put(num, mp2.getOrDefault(num, 0) + 1);
                mp1.put(num, mp1.getOrDefault(num, 0) - 1);
                size++;
            }
        }
        int it = 0;
        int[] res = new int[size];

        for (Map.Entry<Integer, Integer> entry : mp2.entrySet()) {
            for (int i = 0; i < entry.getValue(); i++) {
                res[it] = entry.getKey();
                it++;
            }
        }

        return res;
    }
}
