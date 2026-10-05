import java.util.*;

public class MinMeetingRooms {
    public int minMeetingRooms(List<Interval> intervals) {
        Map<Integer, Integer> map = new TreeMap<>();

        for(Interval interval : intervals) {
            map.put(interval.start, map.getOrDefault(interval.start, 0) + 1);
            map.put(interval.end, map.getOrDefault(interval.end, 0) - 1);
        }

        int currentMeetings = 0;
        int maxMeetings = 0;

        for(Integer key : map.keySet()) {
            currentMeetings += map.get(key);
            maxMeetings = Math.max(maxMeetings, currentMeetings);
        }

        return maxMeetings;
    }
}
