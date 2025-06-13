import java.util.*;

public class ContainsNearbyDuplicate {

    public boolean containsNearbyDuplicate(int[] nums, int k) {
        Map<Integer, Integer> lastIndexMap = new HashMap<>();

        for (int i = 0; i < nums.length; i++) {
            if (lastIndexMap.containsKey(nums[i]))
                if (Math.abs(lastIndexMap.get(nums[i]) - i) <= k) return true;

            lastIndexMap.put(nums[i], i);
        }

        return false;
    }
}
