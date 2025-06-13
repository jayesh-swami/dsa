import java.util.*;

public class SingleNonRepeatedNumber {
    /**
     * XOR property can be used to find the only element which does not appear twice and only appears once.
     * @param nums
     * @return
     */
    public int singleNumber(int[] nums) {
        int res = 0;

        for(int num: nums) res ^= num;

        return res;
    }

    private int singleNumberHashSet(int[] nums) {
        Set<Integer> set = new HashSet<>();

        for(int num: nums) {
            if(set.contains(num)) {
                set.remove(num);
            } else {
                set.add(num);
            }
        }

        return set.iterator().next();
    }
}
