import java.util.HashMap;

public class TwoSum {
    public int[] twoSum(int[] nums, int target) {
        HashMap<Integer, Integer> map = new HashMap<>();
        int index1 = -1, index2 = -1;

        for(int i = 0; i < nums.length ; i++) {
            if(map.containsKey(nums[i])) {
                map.replace(nums[i], map.get(nums[i]) + i);
            } else {
                map.put(nums[i], i);
            }
        }

        for(int i = 0; i < nums.length ; i++) {

            if(map.containsKey(target - nums[i]) && i != map.get(target - nums[i])) {
                if(2 * nums[i] == target) {
                    index1 = i;
                    index2 = map.get(nums[i]) - i;
                } else {
                    index1 = i;
                    index2 = map.get(target - nums[i]);
                }
                break;
            }
        }
        return new int[]{index1, index2};
    }
}
