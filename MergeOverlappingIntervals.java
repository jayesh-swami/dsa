import java.util.*;

public class MergeOverlappingIntervals {
    public int[][] merge(int[][] intervals) {
        Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0]));

        List<int[]> res = new ArrayList<>();

        int n = intervals.length;

        res.add(intervals[0]);

        for(int i = 1; i < n ; i++) {
            if(res.get(res.size() - 1)[1] >= intervals[i][0]) {
                res.get(res.size() - 1)[1] =
                        Math.max(res.get(res.size() - 1)[1], intervals[i][1]);
            } else {
                res.add(intervals[i]);
            }
        }

        return res.toArray(new int[res.size()][]);
    }
}
