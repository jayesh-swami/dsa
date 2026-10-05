import java.util.HashSet;
import java.util.Set;

public class LongestConsecutive {

    public int longestConsecutive(int[] nums) {
        Set<Integer> s = new HashSet<>();
        Set<Integer> starts = new HashSet<>();

        for(int num: nums) {
            s.add(num);
        }

        for(int num: nums) {
            if(!s.contains(num - 1)) starts.add(num);
        }

        int res = 0;

        for(Integer i: starts) {
            int counter = 0;
            int n = i;
            while(s.contains(n)) {
                n++; counter++;
            }
            res = Math.max(res, counter);
        }

        return res;
    }
}
