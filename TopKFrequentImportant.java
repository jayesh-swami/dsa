import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;

public class TopKFrequentImportant {


    /**
     * Create buckets of fequency and put the integers in them
     *
     * SPECIAL NOTE FOR JAVA: while using Collections.nCopies(N, new Object()), java will use the same reference
     * in all the copies and hence initialize accordingly using a for loop and a new Object() every time.
     *
     *
     * @param nums
     * @param k
     * @return
     */
    public static int[] topKFrequent(int[] nums, int k) {
        List<List<Integer>> bucket = new ArrayList<>(Collections.nCopies(1000, null));

        for(int i = 0 ; i< 1000 ; i++) {
            bucket.set(i, new ArrayList<>());
        }

        HashMap<Integer, Integer> map = new HashMap<>();

        for(int num: nums) {
            if(map.containsKey(num)) {
                map.replace(num, map.get(num) + 1);
            } else {
                map.put(num, 1);
            }
        }

        for(Integer key: map.keySet()) {
            bucket.get(map.get(key)).add(key);
        }

        int counter = 0;
        int[] result = new int[k];

        for(int i = 999 ; i >= 0 && counter < k ; i--) {

            for(Integer val: bucket.get(i)) {

                result[counter] = val;
                counter++;

                if(counter == k) {
                    break;
                }
            }
        }

        return result;
    }

}
