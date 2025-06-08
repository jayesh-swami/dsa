import java.util.*;

public class CanAttendMeetings {

    public boolean canAttendMeetings(List<Interval> intervals) {
        intervals.sort(Comparator.comparingInt(i -> i.start));

        for(int i = 1 ; i < intervals.size() ; i++) {
            Interval interval = intervals.get(i);
            Interval prevInteval = intervals.get(i-1);

            if(interval.start < prevInteval.end) return false;
        }

        return true;
    }
}
