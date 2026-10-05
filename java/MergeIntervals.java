import java.util.*;

public class MergeIntervals {

    public int[][] insert(int[][] intervals, int[] newInterval) {
        List<int[]> res = new ArrayList<>();

        int i = 0, n = intervals.length;

        while(i < n && newInterval[0] > intervals[i][1]) {
            res.add(intervals[i]);
            i++;
        }

        while (i < n && newInterval[1] >= intervals[i][0]) {
            newInterval[0] = Math.min(newInterval[0], intervals[i][0]);
            newInterval[1] = Math.max(newInterval[1], intervals[i][1]);
            i++;
        }

        res.add(newInterval);

        while (i < n) {
            res.add(intervals[i]);
            i++;
        }

        return res.toArray(new int[res.size()][]);
    }
}
