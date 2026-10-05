import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ThreeSum {

    public List<List<Integer>> threeSum(int[] nums) {
        Arrays.sort(nums);

        List<List<Integer>> result = new ArrayList<>();

        for(int i = 0 ; i < nums.length ; i++) {
            int j = i + 1, k = nums.length - 1;
            while(j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                if(sum == 0) {
                    result.add(Arrays.asList(nums[i], nums[j], nums[k]));

                    if(nums[j+1] == nums[j]) {
                        j++;
                    } else if(nums[k-1] == nums[k]) {
                        k--;
                    } else {
                        j++;
                        k--;
                    }
                }

                if(sum < 0) j++;

                if(sum > 0) k--;
            }
        }

        return new ArrayList<>(result);
    }

}
