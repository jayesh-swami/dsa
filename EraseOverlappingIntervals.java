import java.util.*;

public class EraseOverlappingIntervals {

    public int eraseOverlapIntervals(int[][] intervals) {

        Arrays.sort(intervals, Comparator.comparingInt(a -> a[0]));
        List<int[]> res = new ArrayList<>();

        res.add(intervals[0]);

        for(int i = 1 ; i < intervals.length ; i++) {

            if(res.get(res.size()-1)[1] > intervals[i][0]) {

                if(res.get(res.size()-1)[1] > intervals[i][1]) {

                    res.set(res.size()-1, intervals[i]);

                }
            } else {

                res.add(intervals[i]);
            }
        }

        return intervals.length - res.size();
    }
}
